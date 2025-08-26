#pragma once
#include "engine/core/core.h"

#include "engine/renderer/Texture.h"

#include <glm/glm.hpp>

namespace Engine {

	enum Components {
		Transform,
		SpriteRenderer,
		Velocity
	};

	struct Component {
		std::string componentName;

		Component() = default;
	};

	struct TransformComponent : public Component {
		glm::vec3 position = glm::vec3(0.f);
		float rotation = 0.f;
		glm::vec2 scale = glm::vec2(1.f);

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

	struct VelocityComponent : public Component {
		glm::vec3 velocity = glm::vec3(0.f);
		float rotationVelocity = 0.f;
		glm::vec2 scaleVelocity = glm::vec2(0.f);

		VelocityComponent() = default;
		VelocityComponent(const VelocityComponent&) = default;
		VelocityComponent(const glm::vec3 velocity)
			: velocity(velocity) {
			componentName = "Velocity";
		}
	};
}