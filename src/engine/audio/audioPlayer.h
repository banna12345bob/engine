#pragma once

#include "engine/core/Window.h"
#include <string>

// Eventually want to remove this
#include <SDL3/SDL.h>

namespace Engine {

	class AudioPlayer
	{
	public:
		virtual ~AudioPlayer() {}
		
		static Scope<AudioPlayer> Create();

		virtual void Run() = 0;
		/**
		@param stringPath must include full path, including the file extension.
		@param loop bool if sound should loop or not
		@param volume must be a float between 0 and 1.
		@param id a pointer that will be set with the ID of the sound if successfully created. (optional)
		*/
		virtual void PlaySound(std::string filePath, bool loop, float_t volume, unsigned int* id = nullptr) = 0;
		virtual void UpdateAudio() = 0;
		virtual void SetLooping(int id, bool value) = 0;
		virtual void SetVolume(int id, float_t value) = 0;
		virtual void StopSound(int id) = 0;

		struct Sound {
			uint8_t* data;
			uint32_t dataLen;
			uint32_t currentOffset;		// Bytes
			uint32_t bufferSize;		// Bytes
			bool loop;					// Putting this after stream breaks the code, probably alignment issues
			SDL_AudioFormat format;
			float_t volume;
			SDL_AudioStream* stream;
			std::string filePath;
		};

		virtual std::unordered_map<int, Ref<Sound>>* GetSounds() = 0;
	};
}