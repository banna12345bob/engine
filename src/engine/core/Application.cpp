#include "Application.h"

#include "engine/debug/Instrumentor.h"

#include "engine/core/Keycodes.h"
#include "engine/events/Key.h"
#include "engine/events/Mouse.h"

#include "engine/renderer/Renderer2D.h"
#include "engine/renderer/RenderCommand.h"

namespace Engine {

	static Application* s_Instance = nullptr;

	Application::Application(WindowProps props)
	{
		EG_PROFILE_FUNCTION();
		s_Instance = this;

		m_Window = Window::Create(props);
		m_EventCallbackManager = new eventCallbackManager();
		m_AudioPlayer = AudioPlayer::Create();
		m_ImGuiRenderer = new ImGuiRenderer();

		m_Window->SetVSync(false);

		getImGuiRenderer()->registerImGuiLayer(m_AudioDebuggerLayer);
		getImGuiRenderer()->registerImGuiLayer(m_RendererStatsLayer);

		m_EventCallbackManager->registerKeyboardCallback(ApplicationKeyboardEventCallback);

		RenderCommand::Init();
		Renderer2D::Init();
	}

	Application::~Application()
	{
		EG_PROFILE_FUNCTION();
		Renderer2D::Shutdown();
	}

	Application* Engine::Application::getApplication()
	{
		return s_Instance;
	}

	void Application::ApplicationKeyboardEventCallback(void* callback) {
		EG_PROFILE_FUNCTION();

		if (Key::wasKeyPressed(EG_KEY_F1)) {
			if (RenderCommand::GetRenderMode() == RenderAPI::RenderMode::Normal)
				RenderCommand::SetRenderMode(RenderAPI::RenderMode::Wireframe);
			else
				RenderCommand::SetRenderMode(RenderAPI::RenderMode::Normal);
		}
		if (Key::wasKeyPressed(EG_KEY_F2))
			Application::getApplication()->m_RendererStatsLayer->m_ShowWindow = !Application::getApplication()->m_RendererStatsLayer->m_ShowWindow;

		if (Key::wasKeyPressed(EG_KEY_F4))
			Application::getApplication()->m_AudioDebuggerLayer->m_ShowWindow = !Application::getApplication()->m_AudioDebuggerLayer->m_ShowWindow;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_layerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Run()
	{
		EG_PROFILE_FUNCTION();

		m_LastFrameTime = SDL_GetTicks();

		while (m_Window->GetRunning()) {
			float time = SDL_GetTicks();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			m_Window->HandleEvents();

			// Need to update mouse every frame
			Engine::Mouse::UpdateMouseState();

			Engine::Renderer2D::ResetStats();
			for (Layer* layer : m_layerStack) {
				layer->OnUpdate(timestep);
				layer->OnRender();
			}

			m_ImGuiRenderer->StartFrame();
			for (Layer* layer : m_layerStack)
				layer->OnImGuiRender();
			m_AudioDebuggerLayer->renderImGUILayer();
			m_RendererStatsLayer->renderImGUILayer();
			m_ImGuiRenderer->EndFrame();

			m_Window->SwapWindow();
		}
	}
}
