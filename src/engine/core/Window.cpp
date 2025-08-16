#include "Window.h"

#ifdef EG_GLFW_WINDOW
#include "platform/GLFW/GLFWWindow.h"
#else
#include "platform/SDL/SDLWindow.h"
#endif

namespace Engine {

	Scope<Window> Window::Create(WindowProps props)
	{
#ifdef EG_GLFW_WINDOW
		// Create GLFW window
		return CreateScope<GLFWWindow>(props);
#else
		// Create SDL window
		return CreateScope<SDLWindow>(props);
#endif

	}
}
