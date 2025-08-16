#pragma once

#include <unordered_map>
#include <SDL3/SDL_mouse.h>
#include "glm/vec2.hpp"

namespace Engine {

	#define EG_MOUSECODE_LEFT 1
	#define EG_MOUSECODE_MIDDLE 2
	#define EG_MOUSECODE_RIGHT 3

	class Mouse {
	public:
		static void UpdateMouseState();

		/**
		* Return true on every frame of key being pressed
		@param int keycode: the id of the key to check
		*/
		static bool isButtonDown(int buttoncode);
		static bool wasButtonPressed(int buttoncode);
		static bool wasButtonReleased(int buttoncode);
		static void setButtonPressed(int buttoncode, bool value);
		
		static void setPosition(int x, int y);
		static void setPosition(glm::vec2 pos);
		static glm::vec2 getPosition() {	return m_Position; };

	private:
		struct MouseButton
		{
		public:
			bool m_IsPressed = false;
			int m_FramesPressed = 0;
		};

		inline static glm::vec2 m_Position;

		inline static std::unordered_map<int, MouseButton> m_MouseButtons;
	};
}