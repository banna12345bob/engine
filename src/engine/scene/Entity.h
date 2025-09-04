#pragma once

#include "Components.h"
#include "BoundingBox.h"
#include "UUID.h"

#include "engine/core/Timestep.h"

namespace Engine {

	class Scene;

	class Entity
	{
	public:
		Entity(std::string name, Scene& scene);

		virtual void OnUpdate(Timestep ts);
		virtual void OnRender();
		TransformComponent* GetTransform();
		SpriteRendererComponent* GetSpriteRenderer();
		VelocityComponent* GetVelocity();
		void Move(glm::vec2 dir, int acceleration, int maxSpeed, Engine::Timestep ts);

		BoundingBox GetBoundingBox(glm::vec2 pos);
	public:
		std::string name;
		bool hide = false;

		bool active = true;

		bool needsDelete = false;

		UUID EntityUUID = UUID(0);
	protected:
		std::unordered_map<Components, Component*> m_Components;
		Scene& m_Scene;
		BoundingBox m_BoundingBox;
	};
}

