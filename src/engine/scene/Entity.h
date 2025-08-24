#pragma once

#include "Components.h"

namespace Engine {

	class Entity
	{
	public:
		Entity(std::string name);

		void Render();
		TransformComponent* GetTransform();
		SpriteRendererComponent* GetSpriteRenderer();
	public:
		std::string name;
		bool hide = false;
	private:
		std::vector<Component*> m_Components;
	};
}

