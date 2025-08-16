#include "Key.h"

#include "engine/debug/Instrumentor.h"

namespace Engine {

	void Key::setKeyPressed(int keycode, bool value)
	{
		EG_PROFILE_FUNCTION();
		m_Keycodes[keycode].m_IsPressed = value;

		if (m_Keycodes[keycode].m_IsPressed)
			m_Keycodes[keycode].m_TimesPressed++;
		else
			m_Keycodes[keycode].m_TimesPressed = 0;
	}

	bool Key::isKeyPressed(int keycode)
	{
		EG_PROFILE_FUNCTION();
		return m_Keycodes[keycode].m_IsPressed;
	}

	bool Key::wasKeyPressed(int keycode)
	{
		EG_PROFILE_FUNCTION();
		if (m_Keycodes[keycode].m_TimesPressed == 0 || m_Keycodes[keycode].m_TimesPressed > 1)
			return false;
		return true;
	}
}
