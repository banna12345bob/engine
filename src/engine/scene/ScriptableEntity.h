#pragma once

#include "Entity.h"

namespace Engine {

	class ScriptableEntity {
	public:
		virtual ~ScriptableEntity() {}

		template<typename T>
		T& GetComponent() {
			return m_Entity.GetComponent<T>();
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return m_Entity.AddComponent<T>(args...);
		}

		Scene* GetScene() {
			return m_Entity.m_Scene;
		}

		Entity GetEntity() { return m_Entity; }

		Entity GetParent() { return m_Entity.getParent(); }
		Entity SetParent(Entity entity) { return m_Entity.setParent(entity); }
		Entity AddChild(Entity entity) { return m_Entity.addChild(entity); }
	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(Timestep ts) {}

	private:
		Entity m_Entity;
		friend class Scene;
	};
}