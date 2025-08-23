#include "GLFWInput.h"

#include <GLFW/glfw3.h>
#include "engine/core/Application.h"

namespace Engine {

	bool GLFWInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::getApplication()->getWindow()->getNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool GLFWInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::getApplication()->getWindow()->getNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> GLFWInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::getApplication()->getWindow()->getNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float GLFWInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float GLFWInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}
