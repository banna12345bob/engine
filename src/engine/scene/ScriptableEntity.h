#pragma once

#include "Entity.h"

namespace Engine {

	class ScriptableEntity {
	public:
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
	private:
		Entity m_Entity;
		friend class Scene;
	};
}