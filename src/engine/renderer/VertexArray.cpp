#include "VertexArray.h"

#include "RenderAPI.h"

#include "platform/OpenGL/OpenGLVertexArray.h"

namespace Engine {

	Ref<VertexArray> VertexArray::Create() 
	{
		switch (RenderAPI::getAPI()) {
		case RenderAPI::API::None: EG_CORE_ASSERT(false, "Cannot have RenderAPI::None");
		case RenderAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
		}

		EG_CORE_ASSERT(false, "Unknown renderAPI");
		return nullptr;
	}

}
