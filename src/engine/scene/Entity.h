#pragma once

#include "Components.h"

#include "engine/core/Timestep.h"

namespace Engine {

	class Entity
	{
	public:
		Entity(std::string name);

		void OnUpdate(Timestep ts);
		void OnRender();
		TransformComponent* GetTransform();
		SpriteRendererComponent* GetSpriteRenderer();
		AccelerationComponent* GetAcceleration();
	public:
		std::string name;
		bool hide = false;
	private:
		std::unordered_map<Components, Component*> m_Components;
	};
}

