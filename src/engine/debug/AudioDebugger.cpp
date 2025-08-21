#include "AudioDebugger.h"

#include "engine/core/Application.h"

#include "engine/core/Keycodes.h"
#include <imgui.h>

namespace Engine {

	AudioDebugger::AudioDebugger()
		: Layer("AudioDebugger")
	{
		DirectoryIterator("assets\\audio");
	}

	void AudioDebugger::OnImGuiRender() {
		EG_PROFILE_FUNCTION();
		if (!this->m_ShowWindow)
			return;

		ImGui::Begin("Audio Debugger", &this->m_ShowWindow);
			if (ImGui::Button("Stop All")) {
				for (auto i = Application::getApplication()->getAudioPlayer()->GetSounds()->begin(); i != Application::getApplication()->getAudioPlayer()->GetSounds()->end(); i++) {
					Application::getApplication()->getAudioPlayer()->StopSound(i->first);
				}
			}
			for (auto i = Application::getApplication()->getAudioPlayer()->GetSounds()->begin(); i != Application::getApplication()->getAudioPlayer()->GetSounds()->end(); i++) {
				// Incase of edge case where threads don't align
				if (Application::getApplication()->getAudioPlayer()->GetSounds()->size() == 0)
					break;

				int id = i->first;
				if (ImGui::TreeNode(std::to_string(id).c_str())) {
					ImGui::Text(i->second->filePath.c_str());
					ImGui::SliderFloat("Volume", &i->second->volume, 0, 1);
					ImGui::Checkbox("Loop", &i->second->loop);
					if (ImGui::Button("Stop"))
						Application::getApplication()->getAudioPlayer()->StopSound(id);
					ImGui::TreePop();
				}
			}
		ImGui::End();

		ImGui::Begin("Audio Debug Player");
			ImGui::Checkbox("Loop", &m_tempLoop);
			ImGui::SliderFloat("Volume", &m_tempVolume, 0, 1);
			for (std::string entry : m_files) {
				if (ImGui::Button(entry.c_str()))
					Application::getApplication()->getAudioPlayer()->PlaySound(entry, m_tempLoop, m_tempVolume);
			}
		ImGui::End();
	}

	void AudioDebugger::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(EG_BIND_EVENT_FN(AudioDebugger::ShowWindow));
	}

	bool AudioDebugger::ShowWindow(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == EG_KEY_F4) {
			m_ShowWindow = !m_ShowWindow;
			return true;
		}
		return false;
	}

	void AudioDebugger::DirectoryIterator(std::filesystem::path path)
	{
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (entry.is_directory())
				DirectoryIterator(entry);
			else
				m_files.push_back(entry.path().string());
		}
	}

}