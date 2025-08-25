#include "Scene.h"

#include "engine/renderer/Renderer2D.h"

namespace Engine {
	void Scene::UpdateScene(Timestep ts)
	{
		for (auto it = m_Entities.begin(); it != m_Entities.end(); it++)
			it->second->OnUpdate(ts);
	}

	void Scene::RenderScene(Camera* camera)
	{
		Renderer2D::BeginScene(camera);
		for (auto it = m_Entities.begin(); it != m_Entities.end(); it++)
		{
			if (it->second->hide)
				continue;

			it->second->OnRender();
		}
		Renderer2D::EndScene();
	}

	void Scene::AddEntity(Entity* entity)
	{
		m_Entities[entity->name] = entity;
	}

	Entity* Scene::GetEntity(std::string name)
	{
		if (m_Entities.contains(name))
			return m_Entities[name];
		else
			EG_CORE_ERROR("Cannot find entity named: {0}", name);
		return nullptr;
	}
}