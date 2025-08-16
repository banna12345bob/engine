#pragma once

#include "engine/audio/audioPlayer.h"

#include "engine/threads/WorkerThread.h"

#include <SDL3/SDL.h>

namespace Engine {

	class SDL_AudioPlayer : public AudioPlayer
	{
	public:
		SDL_AudioPlayer();
		virtual ~SDL_AudioPlayer();
		virtual void PlaySound(std::string filePath, bool loop, float_t volume, unsigned int* id) override;
		virtual void Run() override;
		virtual void UpdateAudio() override;
		virtual void SetLooping(int id, bool value) override;
		virtual void SetVolume(int id, float_t value) override;
		virtual void StopSound(int id) override;

		virtual std::unordered_map<int, Ref<Sound>>* GetSounds() override { return &m_sounds; }

	private:
		void LoadAudio(std::string stringPath, bool loop, float_t volume, uint32_t id);

		SDL_AudioDeviceID m_deviceId;
		SDL_AudioSpec m_deviceSpec;

		std::unordered_map<int, Ref<Sound>> m_sounds;
		int m_nextId;

		std::atomic<bool> m_runningFlag { true };
		std::mutex m_mutex;
		std::thread m_updateThread;

		Engine::WorkerThread m_loadWorkerThread;
	};
}