#include "Texture.h"

#include "RenderAPI.h"

#include "platform/OpenGL/OpenGLTexture.h"

namespace Engine {

	Ref<Texture2D> Texture2D::Create(const uint32_t width, const uint32_t height)
	{
		switch (RenderAPI::getAPI()) {
		case RenderAPI::API::None: EG_CORE_ASSERT(false, "Cannot have RenderAPI::None");
		case RenderAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width, height);
		}

		EG_CORE_ASSERT(false, "Unknown renderAPI");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (RenderAPI::getAPI()) {
		case RenderAPI::API::None: EG_CORE_ASSERT(false, "Cannot have RenderAPI::None");
		case RenderAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
		}

		EG_CORE_ASSERT(false, "Unknown renderAPI");
		return nullptr;
	}

	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, glm::vec2& max, const glm::vec2& coords)
		: m_Texture(texture)
	{
		m_TexCoords[0] = { min.x, min.y };
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };

		m_FlippedTexCoords[0] = m_TexCoords[1];
		m_FlippedTexCoords[1] = m_TexCoords[0];
		m_FlippedTexCoords[2] = m_TexCoords[3];
		m_FlippedTexCoords[3] = m_TexCoords[2];

		glm::vec2 cellsize = { (min.x * texture->getWidth()) / coords.x, (min.y * texture->getHeight()) / coords.y };
		m_SpriteSize = { ((max.x * texture->getWidth()) / cellsize.x) - coords.x, ((max.y * texture->getHeight()) / cellsize.y) - coords.y };
	}

	Ref<Texture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize)
	{
		glm::vec2 min = { (coords.x * cellSize.x) / texture->getWidth()+0.0001f, (coords.y * cellSize.y) / texture->getHeight() };
		glm::vec2 max = { ((coords.x + spriteSize.x) * cellSize.x) / texture->getWidth(), ((coords.y + spriteSize.y) * cellSize.y) / texture->getHeight() };
		return CreateRef<SubTexture2D>(texture, min, max, coords);
	}
}