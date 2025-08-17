#include "Renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>


#include "engine/renderer/VertexArray.h"
#include "engine/renderer/Buffers.h"
#include "engine/renderer/Shader.h"
#include "engine/renderer/RenderCommand.h"

namespace Engine {

	struct SquareVertex
	{
		glm::vec3 position;
		glm::vec4 colour;
		glm::vec2 texCoord;
		float texIndex;
		float tilingFactor;
	};

	struct Renderer2DData
	{
		static const uint32_t maxQuads = 20000;
		static const uint32_t maxVerticies = maxQuads * 4;
		static const uint32_t maxIndices = maxQuads * 6;
		static const uint32_t maxTextureSlots = 32;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		uint32_t squareIndexCount = 0;

		SquareVertex* squareVertexBufferBase = nullptr;
		SquareVertex* squareVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, maxTextureSlots> textureSlots;
		uint32_t textureSlotIndex = 1;

		glm::vec4 quadVertexPosition[4];

		ShaderLibary shaderLibrary;

		Camera* orthoGraphicCamera = nullptr;

		Renderer2D::Statistics Stats;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.maxVerticies * sizeof(SquareVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Colour" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TexIndex" },
			{ ShaderDataType::Float, "a_TilingFactor" }
			});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.squareVertexBufferBase = new SquareVertex[s_Data.maxVerticies];

		uint32_t* squareIndices = new uint32_t[s_Data.maxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.maxIndices; i += 6)
		{
			squareIndices[i + 0] = offset + 0;
			squareIndices[i + 1] = offset + 1;
			squareIndices[i + 2] = offset + 2;

			squareIndices[i + 3] = offset + 2;
			squareIndices[i + 4] = offset + 3;
			squareIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(squareIndices, s_Data.maxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(indexBuffer);
		delete[] squareIndices;

		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[s_Data.maxTextureSlots];
		for (uint32_t i = 0; i < s_Data.maxTextureSlots; i++)
			samplers[i] = i;

		s_Data.TextureShader = s_Data.shaderLibrary.Load("assets/shaders/texture.glsl");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetIntArray("u_Texture", samplers, s_Data.maxTextureSlots);

		s_Data.textureSlots[0] = s_Data.WhiteTexture;

		s_Data.quadVertexPosition[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.quadVertexPosition[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.quadVertexPosition[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.quadVertexPosition[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::Shutdown()
	{
		delete[] s_Data.squareVertexBufferBase;
	}

	void Renderer2D::BeginScene(Camera* camera)
	{
		s_Data.orthoGraphicCamera = camera;
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", s_Data.orthoGraphicCamera->GetViewProjectionMatrix());

		s_Data.squareIndexCount = 0;
		s_Data.squareVertexBufferPtr = s_Data.squareVertexBufferBase;

		s_Data.textureSlotIndex = 1;
	}

	void Renderer2D::EndScene()
	{
		uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.squareVertexBufferPtr - (uint8_t*)s_Data.squareVertexBufferBase);
		s_Data.QuadVertexBuffer->SetData(s_Data.squareVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		if (s_Data.squareIndexCount == 0)
			return; // Nothing to draw

		for (uint32_t i = 0; i < s_Data.textureSlotIndex; i++)
			s_Data.textureSlots[i]->Bind(i);

		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.squareIndexCount);
		s_Data.Stats.DrawCalls++;
	}

	void Renderer2D::FlushAndReset()
	{
		EndScene();

		s_Data.squareIndexCount = 0;
		s_Data.squareVertexBufferPtr = s_Data.squareVertexBufferPtr;

		s_Data.textureSlotIndex = 1;
		BeginScene(s_Data.orthoGraphicCamera);
	}

	void Renderer2D::DrawQuad(glm::vec3 position, glm::vec2 scale, glm::vec4 colour)
	{
		DrawQuad(position, scale, 0, colour);
	}

	void Renderer2D::DrawQuad(glm::vec3 position, glm::vec2 scale, float rotation, glm::vec4 colour)
	{
		if (s_Data.squareIndexCount >= Renderer2DData::maxIndices)
			FlushAndReset();

		constexpr size_t squareVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		const float texIndex = 0.0f;

		const float tilingFactor = 1.0f;

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

		for (size_t i = 0; i < squareVertexCount; i++)
		{
			s_Data.squareVertexBufferPtr->position = transform * s_Data.quadVertexPosition[i];
			s_Data.squareVertexBufferPtr->colour = colour;
			s_Data.squareVertexBufferPtr->texCoord = textureCoords[i];
			s_Data.squareVertexBufferPtr->texIndex = texIndex;
			s_Data.squareVertexBufferPtr->tilingFactor = tilingFactor;
			s_Data.squareVertexBufferPtr++;
		}

		s_Data.squareIndexCount += 6;
		s_Data.Stats.squareCount++;
	}

	void Renderer2D::DrawQuad(glm::vec3 position, glm::vec2 scale, Ref<Texture2D>& texture, glm::vec4 tintColour, float tilingFactor)
	{
		DrawQuad(position, scale, 0, texture, tintColour, tilingFactor);
	}

	void Renderer2D::DrawQuad(glm::vec3 position, glm::vec2 scale, float rotation, Ref<Texture2D>& texture, glm::vec4 tintColour, float tilingFactor)
	{
		if (s_Data.squareIndexCount >= Renderer2DData::maxIndices)
			FlushAndReset();

		constexpr size_t squareVertexCount = 4;


		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.textureSlotIndex; i++)
		{
			if (*s_Data.textureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}
		if (s_Data.textureSlotIndex >= s_Data.maxTextureSlots) 
		{
			//EG_ASSERT(false, "HERE");
			FlushAndReset();
		}

		if (textureIndex == 0.0f)
		{
			if (s_Data.squareIndexCount >= Renderer2DData::maxIndices)
				FlushAndReset();

			textureIndex = (float)s_Data.textureSlotIndex;
			if (texture->isSubTexture())
			{
				Ref<SubTexture2D> subTex = std::static_pointer_cast<SubTexture2D>(texture);
				s_Data.textureSlots[s_Data.textureSlotIndex] = subTex->GetTexture();
			}
			else
				s_Data.textureSlots[s_Data.textureSlotIndex] = texture;
			s_Data.textureSlotIndex++;
		}


		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

		for (size_t i = 0; i < squareVertexCount; i++)
		{
			s_Data.squareVertexBufferPtr->position = transform * s_Data.quadVertexPosition[i];
			s_Data.squareVertexBufferPtr->colour = tintColour;
			s_Data.squareVertexBufferPtr->texCoord = texture->getTextureCoords()[i];
			s_Data.squareVertexBufferPtr->texIndex = textureIndex;
			s_Data.squareVertexBufferPtr->tilingFactor = tilingFactor;
			s_Data.squareVertexBufferPtr++;
		}

		s_Data.squareIndexCount += 6;
		s_Data.Stats.squareCount++;
	}

	void Renderer2D::ResetStats()
	{
		memset(&s_Data.Stats, 0, sizeof(Statistics));
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_Data.Stats;
	}
}