#pragma once

#include "engine/core/Window.h"

#include <GLFW/glfw3.h>

namespace Engine {

	class GLFWWindow : public Window
	{
	public:
		GLFWWindow(WindowProps props);
		void Init(WindowProps props);
		virtual ~GLFWWindow();

		virtual int GetWidth() override { return m_data.width; }
		virtual int GetHeight() override { return m_data.height; }

		virtual void SetWidth(int width) override;
		virtual void SetHeight(int height) override;

		virtual void ReloadWindow() override;

		virtual void SetVSync(bool value) override;
		virtual int GetVSync() override;

		virtual void HandleEvents() override;

		virtual void* getNativeWindow() override { return m_window; }

		virtual void SwapWindow() override { glfwSwapBuffers(m_window); }
	private:
		void CreateGLContext();

		GLFWwindow* m_window;

		WindowProps m_data;
	};
}

