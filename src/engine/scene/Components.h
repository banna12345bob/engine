#pragma once
#include "engine/core/core.h"

#include "engine/renderer/Texture.h"

#include <glm/glm.hpp>

namespace Engine {
	enum Direction {
		NONE = 0,
		LEFT = 1,
		RIGHT = 2,
		UP = 3,
		DOWN = 4
	};

	enum Components {
		Transform,
		SpriteRenderer,
		Acceleration
	};

	struct Component {
		std::string componentName;

		Component() = default;
	};

	struct TransformComponent : public Component {
		glm::vec3 position = glm::vec3(0.f);
		float rotation = 0.f;
		glm::vec2 scale = glm::vec2(32.f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3 position)
			: position(position) {
			componentName = "Transform";
		}
	};

	struct SpriteRendererComponent : public Component {
		glm::vec4 colour = glm::vec4(1.f);
		Ref<Texture2D> texture;
		float tilingFactor = 1.f;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& colour)
			: colour(colour) {
			componentName = "SpritRenderer";
		}
	};

	struct AccelerationComponent : public Component {
		glm::vec3 acceleration = glm::vec3(0.f);
		float rotationAcceleration = 0.f;
		glm::vec2 scaleAcceleration = glm::vec2(0.f);
		Direction currentDirection;

		AccelerationComponent() = default;
		AccelerationComponent(const AccelerationComponent&) = default;
		AccelerationComponent(const glm::vec3 acceleration)
			: acceleration(acceleration) {
			componentName = "Acceleration";
		}
	};
}