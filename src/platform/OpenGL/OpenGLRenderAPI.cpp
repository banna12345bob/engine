#include "OpenGLRenderAPI.h"

#include <glad/glad.h>

#ifdef EG_GLFW_WINDOW
#include <GLFW/glfw3.h>
#else
#include <SDL3/SDL.h>
#endif

#include <glm/gtc/matrix_transform.hpp>

#include "engine/core/Application.h"

namespace Engine {

	static void OpenGLMessageCallback(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         EG_CORE_FATAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       EG_CORE_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          EG_CORE_WARN(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: EG_CORE_TRACE(message); return;
		}

		EG_CORE_FATAL("Unknown severity level!");
	}

	void OpenGLRenderAPI::Init()
	{
#ifdef EG_GLFW_WINDOW
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EG_CORE_ASSERT(status, "Failed to initalise glad");
#else
		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
			EG_CORE_FATAL("GLAD couldn't load OpenGL");
			EG_CORE_ASSERT(false, "GLAD ERROR");
		}
#endif

#ifdef EG_DEBUG

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

#endif // EG_DEBUG

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRenderAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRenderAPI::SetClearColor(const glm::vec4& colour)
	{
		glClearColor(colour.r, colour.g, colour.b, colour.a);
	}

	void OpenGLRenderAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderAPI::setRenderMode(RenderMode renderMode)
	{
		m_RenderMode = renderMode;

		switch (getRenderMode()) {
		case RenderMode::Normal:    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		case RenderMode::Wireframe: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		}
	}

	OpenGLRenderAPI::RenderMode OpenGLRenderAPI::getRenderMode()
	{
		return m_RenderMode;
	}

	void OpenGLRenderAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}