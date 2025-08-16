#pragma once
#include <unordered_map>
#include <SDL3/SDL_scancode.h>

namespace Engine {
	
	class Key {
	public:
		/**
		* Only returns true on first frame of key being pressed
		@param int keycode: the id of the key to check
		*/
		static bool wasKeyPressed(int keycode);
		/**
		* Return true on every frame of key being pressed
		@param int keycode: the id of the key to check
		*/
		static bool isKeyPressed(int keycode);
		static void setKeyPressed(int keycode, bool value);

	private:
		struct Keycode
		{
		public:
			int m_TimesPressed = 0;
			bool m_IsPressed = false;
		};

		inline static std::unordered_map<int, Keycode> m_Keycodes;
	};
}

