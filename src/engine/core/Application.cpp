#include "Application.h"

#include "engine/debug/Instrumentor.h"

#include "engine/core/Keycodes.h"
#include "engine/renderer/Renderer2D.h"
#include "engine/renderer/RenderCommand.h"

#include <GLFW/glfw3.h>

namespace Engine {

	static Application* s_Instance = nullptr;

	Application::Application(Window::WindowProps props)
	{
		EG_PROFILE_FUNCTION();
		s_Instance = this;

		m_Window = Window::Create(props);
		m_Window->SetEventCallback(EG_BIND_EVENT_FN(Application::OnEvent));
		m_Running = true;
		m_AudioPlayer = AudioPlayer::Create();

		m_Window->SetVSync(false);

		RenderCommand::Init();
		Renderer2D::Init();
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		PushLayer(new AudioDebugger);
		PushLayer(new ImGuiRendererStats);
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

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(EG_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(EG_BIND_EVENT_FN(Application::OnWindowResize));
		dispatcher.Dispatch<KeyPressedEvent>(EG_BIND_EVENT_FN(Application::DebugKeys));

		for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it)
		{
			if (e.Handled) 
				break;

			(*it)->OnEvent(e);
		}
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

		m_LastFrameTime = (float)glfwGetTime();
		while (m_Running) {
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			Engine::Renderer2D::ResetStats();
			for (Layer* layer : m_layerStack) {
				layer->OnUpdate(timestep);
				layer->OnRender();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_layerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		m_Window->ReloadWindow();
		RenderCommand::SetViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

	bool Application::DebugKeys(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == EG_KEY_F1 && e.GetRepeatCount() == 0)
		{
			if (RenderCommand::GetRenderMode() == RenderAPI::RenderMode::Normal)
				RenderCommand::SetRenderMode(RenderAPI::RenderMode::Wireframe);
			else
				RenderCommand::SetRenderMode(RenderAPI::RenderMode::Normal);
			return true;
		}
		return false;
	}
}
