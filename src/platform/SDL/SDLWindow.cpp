#include "SDLWindow.h"

#include <stb_image.h>

#include <filesystem>

#include <glad/glad.h>

#include "engine/debug/Instrumentor.h"
#include "engine/core/Application.h"
#include "engine/events/Key.h"
#include "engine/events/Mouse.h"

#include "engine/renderer/RenderAPI.h"
#include "engine/renderer/RenderCommand.h"

namespace Engine {
	bool EventWatcher(void* userdata, SDL_Event* event)
	{
		Application::getApplication()->getImGuiRenderer()->handleImGUIEvents(event);

		switch (event->type) {
		case SDL_EVENT_QUIT:
			Application::getApplication()->getWindow()->SetRunning(false);
			break;
		case SDL_EVENT_WINDOW_RESIZED:
			// TODO: Change OpenGL viewport size
			Application::getApplication()->getWindow()->ReloadWindow();
			break;
		case SDL_EVENT_WINDOW_MINIMIZED:
			// TODO: Add a config option that caps the FPS if window minimized
			EG_CORE_WARN("implement Window Minimized event");
			break;
		case SDL_EVENT_WINDOW_RESTORED:
			EG_CORE_WARN("implement Window Restored events");
			break;
		case SDL_EVENT_KEY_DOWN:
			Key::setKeyPressed(event->key.scancode, true);
			if (Application::getApplication()->getCallbackManager()->getKeyboardCallbacks()->size() == 0) {
				EG_CORE_WARN("No keyboard callbacks registered");
				break;
			}
			for (int i = 0; i < Application::getApplication()->getCallbackManager()->getKeyboardCallbacks()->size(); i++)
				Application::getApplication()->getCallbackManager()->getKeyboardCallbacks()->at(i)(nullptr);
			break;
		case SDL_EVENT_KEY_UP:
			Key::setKeyPressed(event->key.scancode, false);
			break;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			// Need to update mouse every frame, so is done elsewhere.
			/*Mouse::setButtonPressed(event->button.button, true);*/
			for (int i = 0; i < Application::getApplication()->getCallbackManager()->getMouseDownCallbacks()->size(); i++)
				Application::getApplication()->getCallbackManager()->getMouseDownCallbacks()->at(i)(nullptr);
			break;
		case SDL_EVENT_MOUSE_BUTTON_UP:
			Mouse::setButtonPressed(event->button.button, false);
			break;
		case SDL_EVENT_MOUSE_MOTION:
			Mouse::setPosition(event->motion.x, event->motion.y);
			for (int i = 0; i < Application::getApplication()->getCallbackManager()->getMouseMoveCallbacks()->size(); i++)
				Application::getApplication()->getCallbackManager()->getMouseMoveCallbacks()->at(i)(nullptr);
			break;
		}

		return true;
	}

	SDLWindow::SDLWindow(WindowProps props)
		: m_data(props)
	{
		Init(props);
	}

	void SDLWindow::Init(WindowProps props)
	{
		EG_PROFILE_FUNCTION();

		uint32_t WindowFlags = SDL_WINDOW_OPENGL;
		//WindowFlags |= SDL_WINDOW_RESIZABLE;

		EG_CORE_ASSERT(m_data.width > 0 && m_data.height > 0, "Invalid Window size");
		EG_CORE_INFO("Creating SDL3 window {0} ({1}, {2})", m_data.title, m_data.width, m_data.height);

		//Initialize SDL
		if (!SDL_Init(SDL_INIT_VIDEO))
		{
			EG_CORE_FATAL("SDL could not initialize! SDL_Error: {0}", SDL_GetError());
			EG_CORE_ASSERT(false, "SDL ERROR");
		}

		if (m_data.fullscreen) {
			EG_CORE_WARN("Fullscreen is very buggy and unsupported");
			int displaycount;
			const SDL_DisplayMode* DM = SDL_GetCurrentDisplayMode(SDL_GetDisplays(&displaycount)[0]);
			m_data.width = DM->w;
			m_data.height = DM->h;
		}

		m_window = SDL_CreateWindow(m_data.title.c_str(), m_data.width, m_data.height, WindowFlags);

		if (m_window == NULL)
		{
			EG_CORE_FATAL("Window could not be created! SDL_Error: {0}", SDL_GetError());
			EG_CORE_ASSERT(false, "SDL ERROR");
		}

		if (m_data.fullscreen)
			SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);

		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None: EG_CORE_ASSERT(false, "Cannot have GraphicsAPI::None");	break;
		case RenderAPI::API::OpenGL: CreateGLContext();	break;
		}

		SDL_AddEventWatch(EventWatcher, this);

		if (!std::filesystem::exists(m_data.pathToIcon)) {
			m_data.pathToIcon = "";
			EG_CORE_ERROR("Failed to load image: {0}", m_data.pathToIcon);
		}
		if (m_data.pathToIcon == "")
			return;

		// Probably could colapse into it's own createSurfaceFromFile function but I can't be bothered
		int width, height, bytesPerPixel;
		void* data = (void*)stbi_load(m_data.pathToIcon, &width, &height, &bytesPerPixel, 4);

		int pitch;
		pitch = width * bytesPerPixel;
		pitch = (pitch + 3) & ~3;

		uint32_t Rmask, Gmask, Bmask, Amask;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
		Rmask = 0x000000FF;
		Gmask = 0x0000FF00;
		Bmask = 0x00FF0000;
		Amask = (bytesPerPixel == 4) ? 0xFF000000 : 0;
#else
		int s = (bytesPerPixel == 4) ? 0 : 8;
		Rmask = 0xFF000000 >> s;
		Gmask = 0x00FF0000 >> s;
		Bmask = 0x0000FF00 >> s;
		Amask = 0x000000FF >> s;
#endif

		SDL_Surface* icon = SDL_CreateSurfaceFrom(width, height, SDL_GetPixelFormatForMasks(bytesPerPixel * 8, Rmask, Gmask, Bmask, Amask), data, pitch);
		if (icon->pixels)
			SDL_SetWindowIcon(m_window, icon);
		else
			EG_CORE_ASSERT(false, "Failed to load image");
	}

	SDLWindow::~SDLWindow()
	{
		EG_PROFILE_FUNCTION();
		SDL_GL_DestroyContext(m_GLContext);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	void SDLWindow::SetWidth(int width)
	{
		EG_PROFILE_FUNCTION();
		if (width <= 0) {
			EG_CORE_WARN("Invalid window width: {0}", width);
			return;
		}

		m_data.width = width;
		SDL_SetWindowSize(m_window, m_data.width, m_data.height);
	}

	void SDLWindow::SetHeight(int height)
	{
		EG_PROFILE_FUNCTION();
		if (height <= 0) {
			EG_CORE_WARN("Invalid window height: {0}", height);
			return;
		}

		m_data.height = height;
		SDL_SetWindowSize(m_window, m_data.width, m_data.height);
	}

	void SDLWindow::ReloadWindow()
	{
		EG_PROFILE_FUNCTION();
		SDL_GetWindowSize(m_window, &m_data.width, &m_data.height);
		RenderCommand::SetViewport(0, 0, GetWidth(), GetHeight());
	}

	/**
	* If turning VSync on, adaptive VSync will be tried first, then regualr VSync if that doesn't work.
	*/
	void SDLWindow::SetVSync(bool value) {
		if (value) {
			// Try adaptive VSync, if that doesn't work try the normal one
			if (!SDL_GL_SetSwapInterval(-1)) {
				EG_CORE_ERROR("Could not enable adaptive VSync: {0}", SDL_GetError());
				if (!SDL_GL_SetSwapInterval(1)) {
					EG_CORE_ERROR("Could not enable VSync: {0}", SDL_GetError());
				}
			}
		}
		else {
			if (!SDL_GL_SetSwapInterval(0)) {
				EG_CORE_ERROR("Could not disable VSync: {0}", SDL_GetError());
			}
		}

		int state;
		if (!SDL_GL_GetSwapInterval(&state)) {
			EG_CORE_ERROR("Could not get VSync state: {0}", SDL_GetError());
			return;
		}

		switch (state) {
		case 0:
			EG_CORE_INFO("VSync is off.");
			break;
		case 1:
			EG_CORE_INFO("VSync is on.");
			break;
		case -1:
			EG_CORE_INFO("Adaptive VSync is on.");
			break;
		}
	}

	/**
	* Returns current VSync mode
	* @returns 0 for off, 1 for VSync and -1 for adaptive VSync. Returns -2 on error
	*/
	int SDLWindow::GetVSync()
	{
		int state;
		if (!SDL_GL_GetSwapInterval(&state)) {
			EG_CORE_ERROR("Could not get VSync state: {0}", SDL_GetError());
			return -2;
		}
		return state;
	}

	void SDLWindow::HandleEvents()
	{
		SDL_Event e;
		SDL_PollEvent(&e);
	}

	void SDLWindow::CreateGLContext() 
	{
		EG_PROFILE_FUNCTION();
		// Create the OpenGl context
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		m_GLContext = SDL_GL_CreateContext(m_window);
		// Ensure the context was actually initialised
		if (m_GLContext == NULL) {
			EG_CORE_FATAL("SDL could not initialise the OpenGL context! {0}", SDL_GetError());
			EG_CORE_ASSERT(false, "SDL ERROR");
		}
		EG_CORE_INFO("Created OpenGL context");

		SDL_GL_MakeCurrent(m_window, m_GLContext);
	}
}
