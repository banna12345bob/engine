#pragma once

#include "engine/renderer/camera/Camera.h"
#include "engine/core/Timestep.h"
#include "engine/scene/BoundingBox.h"

#include <entt/entt.hpp>

#include <box2d/box2d.h>

namespace Engine {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		virtual void UpdateScene(Timestep ts);
		void RenderScene(Camera* camera);
		Entity AddEntity(const std::string& name);
		Entity AddEntityWithUUID(UUID uuid, const std::string& name);
		Entity GetEntity(UUID uuid);
		Entity GetEntity(std::string name);
		bool RemoveEntity(Entity entity);

		void StartPhysicsWorld();
		void EndPhysicsWorld();
	private:
		void SetUpPhysicsEntity(Entity entity);
	protected:
		entt::registry m_Registry;

		b2WorldId m_Box2dWorldID = b2_nullWorldId;

		std::unordered_map<UUID, entt::entity> m_Entities;

		friend class Entity;
	};
}

