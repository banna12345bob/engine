#pragma once
#include "engine/core/core.h"

#include "engine/renderer/Texture.h"
#include "engine/scene/UUID.h"
#include "engine/renderer/camera/OrthographicCamera.h"

#include "engine/core/Timestep.h"

#include <glm/glm.hpp>

#include <box2d/box2d.h>

namespace Engine {

	struct MetaDataComponent {
		UUID uuid;
		std::string name;
		bool hide;
		UUID parent;
		std::vector<UUID> children;

		MetaDataComponent() = default;
		MetaDataComponent(const MetaDataComponent&) = default;
		MetaDataComponent(const UUID& uuid, const std::string& name, const bool& hide) 
			: uuid(uuid), name(name), hide(hide), parent(0) {}
	};

	struct TransformComponent {
		glm::vec3 position = glm::vec3(0.f);
		float rotation = 0.f;
		glm::vec2 scale = glm::vec2(1.f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3 position)
			: position(position) {}
	};

	struct SpriteRendererComponent {
		glm::vec4 colour = glm::vec4(1.f);
		Ref<Texture2D> texture;
		float tilingFactor = 1.f;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& colour)
			: colour(colour) {}

	private:
		std::string filepath;
	};

	struct OrthographicCameraComponent {
		OrthographicCamera* camera;

		OrthographicCameraComponent() = default;
		OrthographicCameraComponent(const OrthographicCameraComponent&) = default;
	};

	class ScriptableEntity;

	struct NativeScriptComponent {
		ScriptableEntity* Instance = nullptr;

		using InstantiateScript = ScriptableEntity* (*)();
		InstantiateScript InstantiateScriptFunction;

		using DestroyScript = void (*)(NativeScriptComponent*);
		DestroyScript DestroyScriptFunction;

		template<typename T>
		void Bind()
		{
			InstantiateScriptFunction = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScriptFunction = [](NativeScriptComponent* NSC) { delete NSC->Instance; NSC->Instance = nullptr; };
		}
	};

	struct VelocityComponent {
		glm::vec3 velocity;
		float rotationVelocity;
		glm::vec2 scaleVelocity;

		VelocityComponent() = default;
		VelocityComponent(const VelocityComponent&) = default;
		VelocityComponent(const glm::vec3 velocity)
			: velocity(velocity) {}
	};

	struct RigidBody2DComponent {
		enum class BodyType { Static = 0, Dynamic, Kinematic };
		b2BodyId Box2DBodyID = b2_nullBodyId;
		BodyType Type = BodyType::Static;

		bool FixedRotation = false;

		RigidBody2DComponent() = default;
		RigidBody2DComponent(const RigidBody2DComponent&) = default;
	};

	struct BoxCollider2DComponent {
		glm::vec2 Offset = { 0.f, 0.f };
		glm::vec2 Size = { .5f, .5f };

		float Density = 1.f;
		float Friction = .6f;

		BoxCollider2DComponent() = default;
		BoxCollider2DComponent(const BoxCollider2DComponent&) = default;
	};
}