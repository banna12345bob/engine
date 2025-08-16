#pragma once

#include "engine/renderer/RenderAPI.h"


namespace Engine {

	class OpenGLRenderAPI : public RenderAPI
	{
	public:
		virtual void Init() override;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void SetClearColor(const glm::vec4& colour) override;
		virtual void Clear() override;
		
		virtual void setRenderMode(RenderMode renderMode) override;
		virtual RenderMode getRenderMode() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) override;
	private:
		RenderMode m_RenderMode = RenderMode::Normal;
	};
}

