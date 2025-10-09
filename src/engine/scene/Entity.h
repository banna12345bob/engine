#pragma once

#include "Components.h"
#include "UUID.h"
#include "Scene.h"

#include <entt/entt.hpp>

namespace Engine {

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handler, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			EG_CORE_ASSERT(!HasComponent<T>(), "Entity has component");
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandler, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T>
		T& GetComponent()
		{
			EG_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have component");
			return m_Scene->m_Registry.get<T>(m_EntityHandler);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.any_of<T>(m_EntityHandler);
		}

		template<typename T>
		void RemoveComponent()
		{
			EG_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have component");
			m_Scene->m_Registry.remove<T>(m_EntityHandler);
		}

		operator bool() const { return m_EntityHandler != entt::null; }
		operator entt::entity() const { return m_EntityHandler; }
		operator uint32_t() const { return (uint32_t)m_EntityHandler; }

		UUID getUUID() { return GetComponent<MetaDataComponent>().uuid; }
		std::string getName() { return GetComponent<MetaDataComponent>().name; }

		void setParent(Entity parent) {
			if (parent.m_EntityHandler == m_EntityHandler) {
				EG_CORE_ERROR("Cannot parent entity to itself");
				return;
			}
			GetComponent<MetaDataComponent>().parent = parent.getUUID();
			parent.GetComponent<MetaDataComponent>().children.push_back(getUUID());
		}
		Entity getParent() { return m_Scene->GetEntity(GetComponent<MetaDataComponent>().parent); }

		void addChild(Entity child) {
			if (child.m_EntityHandler == m_EntityHandler)
			{
				EG_CORE_ERROR("Cannot parent entity to itself");
				return;
			}
			GetComponent<MetaDataComponent>().children.push_back(child.getUUID()); 
			child.GetComponent<MetaDataComponent>().parent = getUUID();
		}
	private:
		entt::entity m_EntityHandler{ entt::null };
		Scene* m_Scene = nullptr;
		friend class ScriptableEntity;
	};
}

