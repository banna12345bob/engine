#pragma once
#include <vector>
//#include <SDL3/SDL.h>

namespace Engine {
	class eventCallbackManager
	{
	public:
		eventCallbackManager();
		void registerKeyboardCallback(void (*callback)(void*));
		void registerMouseDownCallback(void (*callback)(void*));
		void registerMouseMoveCallback(void (*callback)(void*));

		std::vector<void (*)(void*)>* getKeyboardCallbacks() { return m_KeyboardCallbacks; }
		std::vector<void (*)(void*)>* getMouseDownCallbacks() { return m_MouseDownCallbacks; }
		std::vector<void (*)(void*)>* getMouseMoveCallbacks() { return m_MouseMoveCallbacks; }
	private:
		std::vector<void (*)(void*)>* m_KeyboardCallbacks;
		std::vector<void (*)(void*)>* m_MouseDownCallbacks;
		std::vector<void (*)(void*)>* m_MouseMoveCallbacks;
	};
}

