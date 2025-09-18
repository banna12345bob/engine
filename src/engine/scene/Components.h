#pragma once
#include "engine/core/core.h"

#include "engine/renderer/Texture.h"
#include "engine/scene/UUID.h"

#include <glm/glm.hpp>

#include <box2d/box2d.h>

namespace Engine {

	struct MetaDataComponent {
		UUID uuid;
		std::string name;
		bool hide;

		MetaDataComponent() = default;
		MetaDataComponent(const MetaDataComponent&) = default;
		MetaDataComponent(const UUID& uuid, const std::string& name, const bool& hide) 
			: uuid(uuid), name(name), hide(hide) {}
	};

	struct TransformComponent {
		glm::vec3 position = glm::vec3(0.f);
		float rotation = 0.f;
		glm::vec2 scale = glm::vec2(1.f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3 position)
			: position(position) {}

		void ImGuiRender();
	};

	struct SpriteRendererComponent {
		glm::vec4 colour = glm::vec4(1.f);
		Ref<Texture2D> texture;
		float tilingFactor = 1.f;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& colour)
			: colour(colour) {}

		void ImGuiRender();

	private:
		std::string filepath;
	};

	struct VelocityComponent {
		glm::vec3 velocity = glm::vec3(0.f);
		float rotationVelocity = 0.f;
		glm::vec2 scaleVelocity = glm::vec2(0.f);

		VelocityComponent() = default;
		VelocityComponent(const VelocityComponent&) = default;
		VelocityComponent(const glm::vec3 velocity)
			: velocity(velocity) {}

		void ImGuiRender();
	};

	struct RigidBody2DComponent {
		b2BodyId Box2DBodyID = b2_nullBodyId;

		RigidBody2DComponent() = default;
		RigidBody2DComponent(const RigidBody2DComponent&) = default;
	};
}