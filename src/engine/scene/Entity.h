#pragma once

#include "Components.h"

#include "engine/core/Timestep.h"

namespace Engine {

	struct BoundingBox {
		// Offset refers to offset from position
		float xOffset = 0, yOffset = 0, width = 0, height = 0;
	};

	class Entity
	{
	public:
		Entity(std::string name);

		virtual void OnUpdate(Timestep ts);
		virtual void OnRender();
		TransformComponent* GetTransform();
		SpriteRendererComponent* GetSpriteRenderer();
		VelocityComponent* GetVelocity();
		void Move(glm::vec2 dir, int acceleration, int maxSpeed, Engine::Timestep ts);
	public:
		std::string name;
		bool hide = false;

		bool active = true;
	protected:
		std::unordered_map<Components, Component*> m_Components;
	};
}

