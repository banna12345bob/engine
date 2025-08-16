#include "GLFWWindow.h"

#include "engine/debug/Instrumentor.h"
#include "engine/renderer/RenderCommand.h"

#include <stb_image.h>

namespace Engine {

	static void GLFWErrorCallback(int error, const char* description)
	{
		EG_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	GLFWWindow::GLFWWindow(WindowProps props)
		: m_data(props)
	{
		Init(props);
	}

	void GLFWWindow::Init(WindowProps props)
	{
		EG_PROFILE_FUNCTION();

		EG_CORE_ASSERT(m_data.width > 0 && m_data.height > 0, "Invalid Window size");
		EG_CORE_INFO("Creating GLFW window {0} ({1}, {2})", m_data.title, m_data.width, m_data.height);

		int success = glfwInit();
		EG_CORE_ASSERT(success, "Could not intialise GLFW!");
		glfwSetErrorCallback(GLFWErrorCallback);

	#if defined(EG_DEBUG)
		if (RenderAPI::getAPI() == RenderAPI::API::OpenGL)
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	#endif

		m_window = glfwCreateWindow((int)m_data.width, (int)m_data.height, m_data.title.c_str(), nullptr, nullptr);

		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None: EG_CORE_ASSERT(false, "Cannot have GraphicsAPI::None");	break;
		case RenderAPI::API::OpenGL: CreateGLContext();	break;
		}

		if (props.pathToIcon != "")
		{
			GLFWimage images[1];
			images[0].pixels = stbi_load(props.pathToIcon, &images[0].width, &images[0].height, 0, 4); //rgba channels 
			if (images[0].pixels)
			{
				glfwSetWindowIcon(m_window, 1, images);
			}
			else
			{
				EG_CORE_ERROR("Failed to load image: {0}", props.pathToIcon);
			}
			stbi_image_free(images[0].pixels);
		}
	}

	GLFWWindow::~GLFWWindow()
	{
		glfwDestroyWindow(m_window);
	}

	void GLFWWindow::SetWidth(int width)
	{
		if (width <= 0) {
			EG_CORE_WARN("Invalid window width: {0}", width);
			return;
		}

		m_data.width = width;
		glfwSetWindowSize(m_window, m_data.width, m_data.height);
	}

	void GLFWWindow::SetHeight(int height)
	{
		if (height <= 0) {
			EG_CORE_WARN("Invalid window height: {0}", height);
			return;
		}

		m_data.height = height;
		glfwSetWindowSize(m_window, m_data.width, m_data.height);
	}

	void GLFWWindow::ReloadWindow()
	{
		glfwGetWindowSize(m_window, &m_data.width, &m_data.height);
		RenderCommand::SetViewport(0, 0, GetWidth(), GetHeight());
	}

	void GLFWWindow::SetVSync(bool value)
	{
		if (value)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}

	int GLFWWindow::GetVSync()
	{
		return 0;
	}

	void GLFWWindow::HandleEvents()
	{
	}

	void GLFWWindow::CreateGLContext()
	{
		EG_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_window);
	}
}