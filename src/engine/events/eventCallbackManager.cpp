#include "eventCallbackManager.h"

#include "engine/core/Log.h"

#include "engine/debug/Instrumentor.h"

namespace Engine {

	eventCallbackManager::eventCallbackManager()
	{
		EG_PROFILE_FUNCTION();
		m_KeyboardCallbacks = new std::vector<void (*)(void*)>();
		m_MouseDownCallbacks = new std::vector<void (*)(void*)>();
		m_MouseMoveCallbacks = new std::vector<void (*)(void*)>();
	}

	void eventCallbackManager::registerKeyboardCallback(void (*callback)(void*))
	{
		EG_PROFILE_FUNCTION();
		m_KeyboardCallbacks->push_back(callback);
	}

	void eventCallbackManager::registerMouseDownCallback(void (*callback)(void*))
	{
		EG_PROFILE_FUNCTION();
		m_MouseDownCallbacks->push_back(callback);
	}

	void eventCallbackManager::registerMouseMoveCallback(void (*callback)(void*))
	{
		EG_PROFILE_FUNCTION();
		m_MouseMoveCallbacks->push_back(callback);
	}
}

