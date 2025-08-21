#pragma once

#include "core.h"

#include "engine/core/Window.h"
#include "engine/audio/audioPlayer.h"

#include "engine/events/eventCallbackManager.h"

#include "engine/debug/AudioDebugger.h"
#include "engine/debug/ImGuiRendererStats.h"

#include "engine/ImGui/ImGuiLayer.h"

#include "Layer.h"
#include "LayerStack.h"

namespace Engine {

	class Application
	{
	public:
        Application(Window::WindowProps props);
		virtual ~Application();

		static Application* getApplication();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		virtual void Run();

		Scope<Window>& getWindow() { return m_Window; }
		Scope<AudioPlayer>& getAudioPlayer() { return m_AudioPlayer; }
		eventCallbackManager* getCallbackManager() { EG_CORE_ASSERT(false, "DEPRICATED"); return m_EventCallbackManager;  }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool DebugKeys(KeyPressedEvent& e);
	private:
		Scope<Window> m_Window;
		Scope<AudioPlayer> m_AudioPlayer;
		eventCallbackManager* m_EventCallbackManager;
		ImGuiLayer* m_ImGuiLayer;

		AudioDebugger* m_AudioDebuggerLayer = new AudioDebugger();
		ImGuiRendererStats* m_RendererStatsLayer = new ImGuiRendererStats();

		LayerStack m_layerStack;

		float m_LastFrameTime;
	};

	//	To be defined in client
    Application* CreateApplication();
}
