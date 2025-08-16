#pragma once

#include "engine/audio/audioPlayer.h"
#include "engine/debug/Instrumentor.h"
#include "engine/ImGui/ImGuiLayer.h"

#include <filesystem>

namespace Engine {

	class AudioDebugger : public ImGuiLayer
	{
	public:
		AudioDebugger();

		virtual void renderImGUILayer() override;

		void DirectoryIterator(std::filesystem::path path);

	private:
		float m_tempVolume = 0.5f;
		bool m_tempLoop = false;
		std::vector<std::string> m_files;
	};

}
