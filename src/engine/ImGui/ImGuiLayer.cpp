#include "ImGuiLayer.h"

#include <imgui.h>

#ifdef EG_GLFW_WINDOW
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#else
#include <backends/imgui_impl_sdl3.h>
#endif

#include <backends/imgui_impl_opengl3.h>

#include "engine/core/Application.h"


namespace Engine {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking	
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		ImGui::StyleColorsDark();

#ifdef EG_GLFW_WINDOW
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getApplication()->getWindow()->getNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
#else
		SDL_Window* window = static_cast<SDL_Window*>(Application::getApplication()->getWindow()->getNativeWindow());
		ImGui_ImplSDL3_InitForOpenGL(window, SDL_GL_GetCurrentContext());
#endif

		ImGui_ImplOpenGL3_Init("#version 450");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
#ifdef EG_GLFW_WINDOW
		ImGui_ImplGlfw_Shutdown();
#else
		ImGui_ImplSDL3_Shutdown();
#endif
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		e.Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
		e.Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
	}

	void ImGuiLayer::Begin()
	{
		EG_PROFILE_FUNCTION();

		ImGui_ImplOpenGL3_NewFrame();
#ifdef EG_GLFW_WINDOW
		ImGui_ImplGlfw_NewFrame();
#else
		ImGui_ImplSDL3_NewFrame();
#endif
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		EG_PROFILE_FUNCTION();

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)Application::getApplication()->getWindow()->GetWidth(), (float)Application::getApplication()->getWindow()->GetHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
#ifdef EG_GLFW_WINDOW
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
#else
			SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
			SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
#endif
		}
	}
}