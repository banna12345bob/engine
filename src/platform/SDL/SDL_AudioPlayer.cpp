#include "SDL_AudioPlayer.h"

#include <future>

#include "engine/debug/Instrumentor.h"

namespace Engine {

	SDL_AudioPlayer::SDL_AudioPlayer()
	{
		EG_PROFILE_FUNCTION();
		if (!SDL_Init(SDL_INIT_AUDIO)) {
			EG_CORE_FATAL("SDL could not initialize audio! SDL_Error: {0}", SDL_GetError());
			EG_CORE_ASSERT(false, "SDL ERROR");
		}

		m_deviceId = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
		if (m_deviceId == 0) {
			EG_CORE_FATAL("Couldn't open audio device! SDL_Error: {0}", SDL_GetError());
			EG_CORE_ASSERT(false, "SDL ERROR");
		}

		SDL_GetAudioDeviceFormat(m_deviceId, &m_deviceSpec, nullptr);

		m_nextId = 0;

		m_updateThread = std::thread(&SDL_AudioPlayer::Run, this);
	}

	void SDL_AudioPlayer::Run()
	{
		EG_PROFILE_FUNCTION();
		while (m_runningFlag) {

			std::lock_guard lk(m_mutex);
			SDL_AudioPlayer::UpdateAudio();
		}
	}

	/**
	@param stringPath must include full path, including the file extension.
	@param loop bool if sound should loop or not
	@param volume must be a float between 0 and 1.
	@param id a pointer that will be set with the ID of the sound if successfully created. (optional)
	*/
	void SDL_AudioPlayer::PlaySound(std::string stringPath, bool loop, float_t volume, unsigned int* id)
	{
		EG_PROFILE_FUNCTION();
		uint32_t givenId = m_nextId++;	// Increments after assigning.

		if (id) {
			*id = givenId;
		}

		std::function<void()> func = [this, stringPath, loop, volume, givenId] { LoadAudio(stringPath, loop, volume, givenId); };
		m_loadWorkerThread.AddToQueue(func);
	}
	void SDL_AudioPlayer::LoadAudio(std::string stringPath, bool loop, float_t volume, uint32_t id)
	{
		EG_PROFILE_FUNCTION();
		bool retval = false;
		Ref<Sound> sound = CreateRef<Sound>();
		m_sounds.emplace(id, sound);
		sound->currentOffset = 0;
		sound->loop = loop;
		sound->volume = std::clamp(volume, 0.0f, 1.0f);
		sound->filePath = stringPath;

		SDL_AudioSpec srcspec;

		// Load file
		const char* filePath = stringPath.c_str();
		if (!SDL_LoadWAV(filePath, &srcspec, &sound->data, &sound->dataLen)) {
			EG_CORE_WARN("Couldn't load .wav file '{0}'. Error: {1}", filePath, SDL_GetError());
			return;
		}

		sound->format = srcspec.format;

		// Create and bind audio stream
		sound->stream = SDL_CreateAudioStream(&srcspec, &m_deviceSpec);
		if (!sound->stream) {
			EG_CORE_ERROR("Couldn't create audio stream. Error: {0}", SDL_GetError());
			return;
		}
		else if (!SDL_BindAudioStream(m_deviceId, sound->stream)) {
			EG_CORE_ERROR("Failed to bind '{0}' to device. Error: {1}", filePath, SDL_GetError());
			return;
		}

		// Set buffer size in bytes. Will be equal to 0.5 seconds.
		uint32_t bufferSizeInSamples = (uint32_t)(srcspec.freq * 0.1f);
		uint32_t sampleSize = SDL_AUDIO_BYTESIZE(srcspec.format);
		sound->bufferSize = bufferSizeInSamples * sampleSize;

		std::lock_guard lk(m_mutex);
	}

	void SDL_AudioPlayer::UpdateAudio()
	{
		EG_PROFILE_FUNCTION();
		for (auto it = m_sounds.begin(); it != m_sounds.end(); )
		{
			Ref<Sound> current = it->second;

			if (SDL_GetAudioStreamQueued(current->stream) < current->bufferSize)
			{
				uint32_t bytesToPut = std::min(current->bufferSize, current->dataLen - current->currentOffset);

				// Apply volume control
				std::vector<uint8_t> output(bytesToPut);
				SDL_MixAudio(output.data(), current->data + current->currentOffset, current->format, bytesToPut, current->volume);

				if (!SDL_PutAudioStreamData(current->stream, output.data(), bytesToPut)) {
					EG_CORE_ERROR("Failed to put audio data onto the buffer. Error: {0}", SDL_GetError());
					SDL_DestroyAudioStream(current->stream);
					it = m_sounds.erase(it);
					continue;
				}

				current->currentOffset += bytesToPut;

				if (current->currentOffset >= current->dataLen) {
					if (current->loop) {
						current->currentOffset = 0;
					}
					else {
						SDL_DestroyAudioStream(current->stream);
						it = m_sounds.erase(it);
						continue;
					}
				}
			}

			it++;
		}
	}

	void SDL_AudioPlayer::SetLooping(int id, bool value)
	{
		EG_PROFILE_FUNCTION();
		std::function<void()> func = [this, id, value] {
			std::lock_guard lk(m_mutex);
			if (m_sounds.count(id)) {
				m_sounds[id]->loop = value;
			}
		};

		m_loadWorkerThread.AddToQueue(func);
	}

	void SDL_AudioPlayer::SetVolume(int id, float_t value)
	{
		EG_PROFILE_FUNCTION();
		std::function<void()> func = [this, id, value] {
			std::lock_guard lk(m_mutex);
			if (m_sounds.count(id)) {
				m_sounds[id]->volume = std::clamp(value, 0.0f, 1.0f);
			}
		};

		m_loadWorkerThread.AddToQueue(func);
	}

	void SDL_AudioPlayer::StopSound(int id)
	{
		EG_PROFILE_FUNCTION();
		std::function<void()> func = [this, id] {
			std::lock_guard lk(m_mutex);
			if (m_sounds.count(id)) {
				m_sounds.erase(id);
			}
		};

		m_loadWorkerThread.AddToQueue(func);
	}

	SDL_AudioPlayer::~SDL_AudioPlayer()
	{
		EG_PROFILE_FUNCTION();
		m_runningFlag = false;
		if (m_updateThread.joinable()) {
			m_updateThread.join();
			m_loadWorkerThread.ExitThread();
		}
	}
}