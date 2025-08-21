#include "Mouse.h"

#include "engine/debug/Instrumentor.h"

namespace Engine {

	void Mouse::UpdateMouseState() {
		EG_CORE_ASSERT(false, "DEPRECATED");
		SDL_MouseButtonFlags flags = SDL_GetMouseState(NULL, NULL);

		Mouse::setButtonPressed(EG_MOUSECODE_LEFT, flags & SDL_BUTTON_LMASK);
		Mouse::setButtonPressed(EG_MOUSECODE_MIDDLE, flags & SDL_BUTTON_MMASK);
		Mouse::setButtonPressed(EG_MOUSECODE_RIGHT, flags & SDL_BUTTON_RMASK);
	}

	void Mouse::setButtonPressed(int buttoncode, bool value)
	{
		EG_PROFILE_FUNCTION();
		EG_CORE_ASSERT(false, "DEPRECATED");
		m_MouseButtons[buttoncode].m_IsPressed = value;

		if (m_MouseButtons[buttoncode].m_IsPressed)
			m_MouseButtons[buttoncode].m_FramesPressed++;
		else
			m_MouseButtons[buttoncode].m_FramesPressed = 0;
	}

	bool Mouse::isButtonDown(int buttoncode)
	{
		EG_PROFILE_FUNCTION();
		EG_CORE_ASSERT(false, "DEPRECATED");
		return m_MouseButtons[buttoncode].m_IsPressed;
	}
	bool Mouse::wasButtonPressed(int buttoncode)
	{
		EG_PROFILE_FUNCTION();
		//EG_TRACE("{0}", m_MouseButtons[buttoncode].m_framesPressed);
		EG_CORE_ASSERT(false, "DEPRECATED");
		return m_MouseButtons[buttoncode].m_FramesPressed == 1;
	}

	void Mouse::setPosition(int x, int y) {
		EG_CORE_ASSERT(false, "DEPRECATED");
		m_Position = { x, y };
	}

	void Mouse::setPosition(glm::vec2 pos) {
		EG_CORE_ASSERT(false, "DEPRECATED");
		m_Position = pos;
	}
}