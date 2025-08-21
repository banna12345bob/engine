#pragma once

#include "engine/core/Window.h"

#include <SDL3/SDL.h>

namespace Engine {

	class SDLWindow : public Window
	{
	public:
		SDLWindow(WindowProps props);
		void Init(WindowProps props);
		virtual ~SDLWindow();

		virtual int GetWidth() override  { return m_data.width; }
		virtual int GetHeight() override { return m_data.height; }

		virtual void SetWidth(int width) override;
		virtual void SetHeight(int height) override;

		virtual void ReloadWindow() override;

		virtual void SetVSync(bool value) override;
		virtual int GetVSync() override;

		virtual void* getNativeWindow() override { return m_window; }

		virtual void SwapWindow() override { SDL_GL_SwapWindow(m_window); }
	private:
		void CreateGLContext();

		SDL_Window* m_window;

		WindowProps m_data;
		SDL_GLContext m_GLContext;
	};

}

