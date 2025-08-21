#pragma once

#include "engine/audio/audioPlayer.h"
#include "engine/debug/Instrumentor.h"
#include "engine/core/Layer.h"
#include "engine/events/AllEvents.h"

#include <filesystem>

namespace Engine {

	class AudioDebugger : public Layer
	{
	public:
		AudioDebugger();
		~AudioDebugger() = default;

		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;
	private:
		void DirectoryIterator(std::filesystem::path path);
		bool ShowWindow(KeyPressedEvent& e);

	private:
		bool m_ShowWindow = false;
		float m_tempVolume = 0.5f;
		bool m_tempLoop = false;
		std::vector<std::string> m_files;
	};

}
