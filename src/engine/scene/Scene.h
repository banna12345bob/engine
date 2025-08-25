#pragma once

#include "Entity.h"
#include "engine/renderer/camera/Camera.h"

namespace Engine {

	class Scene
	{
	public:
		Scene() = default;

		void UpdateScene(Timestep ts);
		void RenderScene(Camera* camera);
		void AddEntity(Entity* entity);
		Entity* GetEntity(std::string name);
	private:
		std::unordered_map<std::string, Entity*> m_Entities;
	};
}

