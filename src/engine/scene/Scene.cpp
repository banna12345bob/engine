#include "Scene.h"
#include <vector>

#include "engine/renderer/Renderer2D.h"
#include "Entity.h"

namespace Engine {
	void Scene::UpdateScene(Timestep ts)
	{
		auto view = m_Registry.view<VelocityComponent>();
		for (auto entity : view)
		{
			VelocityComponent& VC = view.get<VelocityComponent>(entity);
			Entity{ entity, this }.GetComponent<TransformComponent>().rotation += VC.rotationVelocity * ts.GetSeconds();
			Entity{ entity, this }.GetComponent<TransformComponent>().scale += VC.scaleVelocity * ts.GetSeconds();
			Entity{ entity, this }.GetComponent<TransformComponent>().position += VC.velocity * ts.GetSeconds();
		}
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
		float padding = 0.000002f;

		if (displacement.x != 0) {
			newBox.x += displacement.x;
			for (auto it = m_CollisionBoxes.begin(); it != m_CollisionBoxes.end(); it++) {
				if (newBox.Intersect(*it->second)) {
					if (displacement.x > 0) {
						actualDisplacement.x = displacement.x - (newBox.right() - it->second->left()) - padding;
					}
					else {
						actualDisplacement.x = displacement.x + (it->second->right() - newBox.left()) + padding;
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
				if (newBox.Intersect(*it->second)) {
					if (displacement.y > 0) {
						actualDisplacement.y = displacement.y - (newBox.top() - it->second->bottom()) - padding;
					}
					else {
						actualDisplacement.y = displacement.y + (it->second->top() - newBox.bottom()) + padding;
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

		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			if (Entity{ entity, this }.GetComponent<MetaDataComponent>().hide)
				continue;

			auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
			if (sprite.texture)
				Renderer2D::DrawQuad(transform.position, transform.scale, transform.rotation, sprite.texture, sprite.colour, sprite.tilingFactor);
			else
				Renderer2D::DrawQuad(transform.position, transform.scale, transform.rotation, sprite.colour);
		}

		// Render walls
		//for (auto it = m_CollisionBoxes.begin(); it != m_CollisionBoxes.end(); it++) {
		//	Renderer2D::DrawQuad(glm::vec3(it->x + it->width / 2, it->y + it->height / 2, 0), it->size(), 0.f, glm::vec4(1, 1, 0, 1));
		//}

		Renderer2D::EndScene();
	}

	Entity Scene::AddEntity(const std::string& name)
	{
		return AddEntityWithUUID(UUID::GenerateUUID(), name);
	}

	Entity Scene::AddEntityWithUUID(UUID uuid, const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<MetaDataComponent>(uuid, name, false);
		entity.AddComponent<TransformComponent>();

		m_Entities[uuid] = entity;

		return entity;
	}

	void Scene::AddCollisionBox(BoundingBox* box, UUID* uuid)
	{
		UUID boxUUID = UUID::GenerateUUID();
		if (uuid)
		{
			*uuid = boxUUID;
		}
		box->BoxUUID = boxUUID;
		m_CollisionBoxes[boxUUID] = box;
	}
	bool Scene::RemoveCollisionBox(UUID uuid)
	{
		m_CollisionBoxes.erase(uuid);
		return true;
	}
	//void Scene::AddCollisionBoxes(std::vector<BoundingBox> boxes)
	//{
	//	m_CollisionBoxes.insert(m_CollisionBoxes.end(), boxes.begin(), boxes.end());
	//}

	Entity Scene::GetEntity(UUID uuid)
	{
		if (m_Entities.find(uuid) != m_Entities.end())
			return { m_Entities.at(uuid), this };
		else
			EG_CORE_ERROR("Cannot find entity named: {0}", uuid.ID);
		return {};
	}

	Entity Scene::GetEntity(std::string name)
	{
		auto view = m_Registry.view<MetaDataComponent>();
		for (auto entity : view)
		{
			const MetaDataComponent& MDC = view.get<MetaDataComponent>(entity);
			if (MDC.name == name)
			{
				return Entity{ entity, this };
			}
		}
		return {};
	}

	bool Scene::RemoveEntity(Entity entity)
	{
		m_Entities.erase(entity.getUUID());
		m_Registry.destroy(entity);
		return true;
	}

}