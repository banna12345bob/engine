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

	std::string ComponentToString(Components component);

	struct Component {
		Component() = default;
		virtual void ImGuiRender() = 0;
	};

	struct TransformComponent : public Component {
		glm::vec3 position = glm::vec3(0.f);
		float rotation = 0.f;
		glm::vec2 scale = glm::vec2(1.f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3 position)
			: position(position) {}

		virtual void ImGuiRender() override;
	};

	struct SpriteRendererComponent : public Component {
		glm::vec4 colour = glm::vec4(1.f);
		Ref<Texture2D> texture;
		float tilingFactor = 1.f;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& colour)
			: colour(colour) {}

		virtual void ImGuiRender() override;
	};

	struct VelocityComponent : public Component {
		glm::vec3 velocity = glm::vec3(0.f);
		float rotationVelocity = 0.f;
		glm::vec2 scaleVelocity = glm::vec2(0.f);

		VelocityComponent() = default;
		VelocityComponent(const VelocityComponent&) = default;
		VelocityComponent(const glm::vec3 velocity)
			: velocity(velocity) {}

		virtual void ImGuiRender() override;
	};
}