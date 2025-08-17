#pragma once

#include <glm/glm.hpp>

#include <string>

#include "engine/core/core.h"
#include "engine/renderer/Texture.h"
#include "engine/renderer/camera/Camera.h"

namespace Engine {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(Camera* camera);
		static void EndScene();

		static void Flush();

		/** Draw square
		@param position: Just your x, y and z position
		@param scale: x scale and y scale
		@param colour: r,g,b,a
		*/
		static void DrawQuad(glm::vec3 position, glm::vec2 scale, glm::vec4 colour);

		/** Draw square with rotation
		@param position: Just your x, y and z position
		@param scale: x scale and y scale
		@param rotation: Rotation in degrees
		@param colour: r,g,b,a
		*/
		static void DrawQuad(glm::vec3 position, glm::vec2 scale, float rotation, glm::vec4 colour);

		/** Draw textured square
		@param position: Just your x, y and z position
		@param scale: x scale and y scale
		@param texture: a Ref to a Texture2D object
		@param tintColour: r,g,b,a
		*/
		static void DrawQuad(glm::vec3 position, glm::vec2 scale, Ref<Texture2D>& texture, glm::vec4 tintColour = glm::vec4(1.0f), float tilingFactor = 1.0f);
		static void DrawQuad(glm::vec3 position, glm::vec2 scale, float rotation, Ref<Texture2D>& texture, glm::vec4 tintColour = glm::vec4(1.0f), float tilingFactor = 1.0f);

		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t squareCount = 0;

			uint32_t GetTotalVertexCount() { return squareCount * 4; }
			uint32_t GetTotalIndexCount() { return squareCount * 6; }
		};
		static void ResetStats();
		static Statistics GetStats();
	private:
		static void FlushAndReset();
	};
}

