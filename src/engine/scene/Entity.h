#pragma once

#include "Components.h"

#include "engine/core/Timestep.h"

namespace Engine {

	class Entity
	{
	public:
		Entity(std::string name);

		virtual void OnUpdate(Timestep ts);
		virtual void OnRender();
		TransformComponent* GetTransform();
		SpriteRendererComponent* GetSpriteRenderer();
		VelocityComponent* GetVelocity();
	public:
		std::string name;
		bool hide = false;
	protected:
		std::unordered_map<Components, Component*> m_Components;
	};
}

