#pragma once
#include "engine/debug/Instrumentor.h"

#if defined(EG_PLATFORM_WINDOWS) || defined(EG_PLATFORM_MACOS_ARM64) || defined(EG_PLATFORM_MACOS_x86)

extern Engine::Application* Engine::CreateApplication();

	int main(int argc, char** argv)
	{
		Engine::Log::Init();

		EG_PROFILE_BEGIN_SESSION("Startup", "EngineProfile-Startup.json");
		auto app = Engine::CreateApplication();
		EG_PROFILE_END_SESSION();

		EG_PROFILE_BEGIN_SESSION("Runtime", "EngineProfile-Runtime.json");
		app->Run();
		EG_PROFILE_END_SESSION();

		EG_PROFILE_BEGIN_SESSION("Shutdown", "EngineProfile-Shutdown.json");
		delete app;
		EG_PROFILE_END_SESSION();

		return 0;
	}
#else
    #error "Entry point not built for current OS!"
#endif
