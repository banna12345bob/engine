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
		void AddEntity(Entity* entity, UUID* uuid = nullptr);
		Entity* GetEntity(UUID uuid);
		void AddCollisionBox(BoundingBox box);
		void AddCollisionBoxes(std::vector<BoundingBox> boxes);
		bool CheckCollisions(BoundingBox box, glm::vec2 vel, glm::vec2& actualDisplacement);
	private:
		std::unordered_map<UUID, Entity*> m_Entities;
		std::vector<BoundingBox> m_CollisionBoxes;
	};
}

