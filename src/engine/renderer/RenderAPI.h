#pragma once

#include "engine/core/core.h"

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Engine {

	class RenderAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};

		enum RenderMode {
			Normal,
			Wireframe
		};

	public:
		virtual void Init() = 0;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void SetClearColor(const glm::vec4& colour) = 0;
		virtual void Clear() = 0;

		virtual void setRenderMode(RenderMode renderMode) = 0;
		virtual RenderMode getRenderMode() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) = 0;

		static RenderAPI::API getAPI();

		static Scope<RenderAPI> Create();

	private:
		static RenderAPI::API s_API;
	};
}

