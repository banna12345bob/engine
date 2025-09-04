#pragma once

#include "core.h"

#include "engine/core/Window.h"
#include "engine/audio/audioPlayer.h"

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

		bool isRunning() { return m_Running; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool DebugKeys(KeyPressedEvent& e);
	private:
		Scope<Window> m_Window;
		Scope<AudioPlayer> m_AudioPlayer;
		ImGuiLayer* m_ImGuiLayer;

		LayerStack m_layerStack;

		float m_LastFrameTime;

		bool m_Running;
	};

	//	To be defined in client
    Application* CreateApplication();
}
