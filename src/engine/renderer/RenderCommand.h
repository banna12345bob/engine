#pragma once

#include "engine/renderer/RenderAPI.h"

namespace Engine {

	class RenderCommand
	{
	public:
		inline static void Init() 
		{
			s_RenderAPI->Init();
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RenderAPI->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RenderAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RenderAPI->Clear();
		}

		inline static RenderAPI::RenderMode GetRenderMode()
		{
			return s_RenderAPI->getRenderMode();
		}

		inline static void SetRenderMode(const RenderAPI::RenderMode renderMode)
		{
			s_RenderAPI->setRenderMode(renderMode);
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0)
		{
			s_RenderAPI->DrawIndexed(vertexArray, count);
		}

	private:
		static Scope<RenderAPI> s_RenderAPI;
	};

}

