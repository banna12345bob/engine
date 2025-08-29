#include "Scene.h"
#include <vector>

#include "engine/renderer/Renderer2D.h"

namespace Engine {
	void Scene::UpdateScene(Timestep ts)
	{
		for (auto it = m_Entities.begin(); it != m_Entities.end(); it++)
			if (it->second->active)
				it->second->OnUpdate(ts);
	}

	/**
	* @param box: the current bounding box of the entity
	* @param displacement: the velocity of the entity * timestep
	* @param actualDisplacement: reference to the resulting displacement that the entity is able to move without overlapping walls
	*/
	bool Scene::CheckCollisions(BoundingBox box, glm::vec2 displacement, glm::vec2& actualDisplacement) {
		BoundingBox newBox = box;
		bool collide = false;
		actualDisplacement = displacement;

		// This is needed because we are working with floats which can be a little inaccurate
		float padding = 0.005f;

		if (displacement.x != 0) {
			newBox.x += displacement.x;
			for (auto it = m_CollisionBoxes.begin(); it != m_CollisionBoxes.end(); it++) {
				if (newBox.Intersect(*it)) {
					if (displacement.x > 0) {
						actualDisplacement.x = displacement.x - (newBox.right() - it->left()) - padding;
					}
					else {
						actualDisplacement.x = displacement.x + (it->right() - newBox.left()) + padding;
					}
					collide = true;
					break;
				}
			}

			newBox.x = box.x;
		}
		
		if (displacement.y != 0) {
			newBox.y += displacement.y;
			for (auto it = m_CollisionBoxes.begin(); it != m_CollisionBoxes.end(); it++) {
				if (newBox.Intersect(*it)) {
					if (displacement.y > 0) {
						actualDisplacement.y = displacement.y - (newBox.top() - it->bottom()) - padding;
					}
					else {
						actualDisplacement.y = displacement.y + (it->top() - newBox.bottom()) + padding;
					}
					collide = true;
					break;
				}
			}
		}

		return collide;
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

		// Render walls
		for (auto it = m_CollisionBoxes.begin(); it != m_CollisionBoxes.end(); it++) {
			Renderer2D::DrawQuad(glm::vec3(it->x + it->width / 2, it->y + it->height / 2, 0), it->size(), 0.f, glm::vec4(1, 1, 0, 1));
		}

		Renderer2D::EndScene();
	}

	void Scene::AddEntity(Entity* entity)
	{
		m_Entities[entity->name] = entity;
	}

	void Scene::AddCollisionBox(BoundingBox box)
	{
		m_CollisionBoxes.push_back(box);
	}
	void Scene::AddCollisionBoxes(std::vector<BoundingBox> boxes)
	{
		m_CollisionBoxes.insert(m_CollisionBoxes.end(), boxes.begin(), boxes.end());
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