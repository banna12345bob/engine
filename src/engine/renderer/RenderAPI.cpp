#include "RenderAPI.h"

#include "platform/OpenGL/OpenGLRenderAPI.h"

namespace Engine {

	RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;

	Scope<RenderAPI> RenderAPI::Create() 
	{
		switch (s_API) 
		{
		case RenderAPI::API::None:		EG_CORE_ASSERT(false, "Cannot have RenderAPI::None"); return nullptr;
		case RenderAPI::API::OpenGL:	return CreateScope<OpenGLRenderAPI>();
		}

		EG_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}

	RenderAPI::API RenderAPI::getAPI()
	{
		return s_API;
	}

}