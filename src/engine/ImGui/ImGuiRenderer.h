#pragma once

#include <vector>

#include "engine/ImGui/ImGUILayer.h"

#include <SDL3/SDL.h>

namespace Engine {

	class ImGuiRenderer
	{
	public:
		ImGuiRenderer();
		~ImGuiRenderer();

		void StartFrame();
		void EndFrame();

		void registerImGuiLayer(ImGuiLayer* ImGuiLayer) { m_ImGuiLayers.push_back(ImGuiLayer); }

		void handleImGUIEvents(const SDL_Event* event);
	private:
		std::vector<ImGuiLayer*> m_ImGuiLayers;
	};
}

