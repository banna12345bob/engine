#pragma once

#include "engine/core/core.h"

#include <glm/glm.hpp>

namespace Engine {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;
		virtual const glm::vec2* getTextureCoords() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual bool operator==(const Texture& other) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		virtual const glm::vec2* getTextureCoords() const override {
			if (m_Flipped)
				return m_FlippedTexCoords;
			return m_TexCoords;
		}

		virtual bool isSubTexture() { return false; }

		virtual void flipAcrossYAxis(bool value) { m_Flipped = value; }

		static Ref<Texture2D> Create(const uint32_t width, const uint32_t height);
		static Ref<Texture2D> Create(const std::string& path);
	private:
		glm::vec2 m_TexCoords[4] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f }
		};
		glm::vec2 m_FlippedTexCoords[4] = {
			{ 1.0f, 0.0f },
			{ 0.0f, 0.0f },
			{ 0.0f, 1.0f },
			{ 1.0f, 1.0f }
		};
		bool m_Flipped = false;
	};

	class SubTexture2D : public Texture2D
	{
	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, glm::vec2& max, const glm::vec2& coords = { 1,1 });

		virtual uint32_t getWidth() const override { return m_Texture->getWidth(); }
		virtual uint32_t getHeight() const override { return m_Texture->getHeight(); }
		virtual const glm::vec2* getTextureCoords() const override { 
			if (m_Flipped)
				return m_FlippedTexCoords;
			return m_TexCoords; }
		virtual void flipAcrossYAxis(bool value) override { m_Flipped = value;	}

		virtual bool isSubTexture() override { return true; }

		virtual void SetData(void* data, uint32_t size) override { m_Texture->SetData(data, size); }

		virtual void Bind(uint32_t slot = 0) const override { m_Texture->Bind(); }
		virtual bool operator==(const Texture& other) const override { return m_Texture->operator==(other); }

		const Ref<Texture2D> GetTexture() const { return m_Texture; }
		const glm::vec2 GetSpriteSize() const { return m_SpriteSize; }

		static Ref<Texture2D> CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = { 1,1 });
	private:
		Ref<Texture2D> m_Texture;

		glm::vec2 m_TexCoords[4];
		glm::vec2 m_FlippedTexCoords[4];
		glm::vec2 m_SpriteSize;
		bool m_Flipped = false;
	};
}

