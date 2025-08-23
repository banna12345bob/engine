#include "Input.h"

#ifdef EG_GLFW_WINDOW
#include "platform/GLFW/GLFWInput.h"
#endif

namespace Engine {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
#ifdef EG_GLFW_WINDOW
		return CreateScope<GLFWInput>();
#else
		EG_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}