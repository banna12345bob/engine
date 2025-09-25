#include "Scene.h"
#include <vector>

#include "engine/renderer/Renderer2D.h"
#include "Entity.h"
#include "engine/utils/Physcis2D.h"
#include "ScriptableEntity.h"

#include "engine/debug/Instrumentor.h"

namespace Engine {
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
		EndPhysicsWorld();
	}

	void Scene::UpdateScene(Timestep ts)
	{
		EG_PROFILE_FUNCTION();
		auto NativeScriptView = m_Registry.view<NativeScriptComponent>();
		for (auto e : NativeScriptView)
		{
			Entity entity{ e, this };
			NativeScriptComponent& NSC = entity.GetComponent<NativeScriptComponent>();

			if (!NSC.Instance)
			{
				NSC.Instance = NSC.InstantiateScriptFunction();
				NSC.Instance->m_Entity = entity;
				NSC.Instance->OnCreate();
			}

			NSC.Instance->OnUpdate(ts);
		}

		if (B2_IS_NULL(m_Box2dWorldID))
			StartPhysicsWorld();

		b2World_Step(m_Box2dWorldID, ts.GetSeconds(), 4);

		auto view = m_Registry.view<RigidBody2DComponent>();
		for (auto e : view)
		{
			Entity entity{ e, this };
			TransformComponent& transform = entity.GetComponent<TransformComponent>();
			RigidBody2DComponent& rb2d = entity.GetComponent<RigidBody2DComponent>();

			if (B2_IS_NULL(rb2d.Box2DBodyID))
			{
				SetUpPhysicsEntity(entity);
			}
			transform.position = { b2Body_GetPosition(rb2d.Box2DBodyID).x, b2Body_GetPosition(rb2d.Box2DBodyID).y, transform.position.z };
			transform.rotation = glm::degrees(b2Rot_GetAngle(b2Body_GetRotation(rb2d.Box2DBodyID)));
		}
	}

	void Scene::RenderScene()
	{
		EG_PROFILE_FUNCTION();
		Renderer2D::BeginScene(Entity{m_PrimaryCamera, this}.GetComponent<OrthographicCameraComponent>().camera);
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

		Renderer2D::EndScene();
	}

	Entity Scene::AddEntity(const std::string& name)
	{
		return AddEntityWithUUID(UUID::GenerateUUID(), name);
	}

	Entity Scene::AddEntityWithUUID(UUID uuid, const std::string& name)
	{
		EG_PROFILE_FUNCTION();
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<MetaDataComponent>(uuid, name, false);
		entity.AddComponent<TransformComponent>();

		m_Entities[uuid] = entity;

		return entity;
	}

	Entity Scene::GetEntity(UUID uuid)
	{
		EG_PROFILE_FUNCTION();
		if (m_Entities.find(uuid) != m_Entities.end())
			return { m_Entities.at(uuid), this };
		else
			EG_CORE_ERROR("Cannot find entity named: {0}", uuid.ID);
		return {};
	}

	Entity Scene::GetEntity(std::string name)
	{
		EG_PROFILE_FUNCTION();
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

	void Scene::StartPhysicsWorld()
	{
		EG_PROFILE_FUNCTION();
		if (B2_IS_NON_NULL(m_Box2dWorldID))
		{
			EndPhysicsWorld();
		}
		b2WorldDef box2dWorldDef = b2DefaultWorldDef();
		box2dWorldDef.gravity = { 0, -9.8f };

		m_Box2dWorldID = b2CreateWorld(&box2dWorldDef);

		auto view = m_Registry.view<RigidBody2DComponent>();
		for (auto e : view)
		{
			Entity entity{ e, this };
			SetUpPhysicsEntity(entity);
		}

		EG_CORE_INFO("Started physics world!");
	}

	void Scene::SetUpPhysicsEntity(Entity entity)
	{
		EG_PROFILE_FUNCTION();
		TransformComponent& transform = entity.GetComponent<TransformComponent>();
		RigidBody2DComponent& rb2d = entity.GetComponent<RigidBody2DComponent>();

		if (B2_IS_NON_NULL(rb2d.Box2DBodyID))
		{
			b2DestroyBody(rb2d.Box2DBodyID);
			rb2d.Box2DBodyID = b2_nullBodyId;
		}

		b2BodyDef bodyDef = b2DefaultBodyDef();
		bodyDef.position = { transform.position.x, transform.position.y };
		bodyDef.rotation = { glm::cos(glm::radians(transform.rotation)), glm::sin(glm::radians(transform.rotation)) };

		bodyDef.type = Utils::RigidBodyTypeToBox2DType(rb2d.Type);
		bodyDef.motionLocks.angularZ = rb2d.FixedRotation;

		rb2d.Box2DBodyID = b2CreateBody(m_Box2dWorldID, &bodyDef);

		if (entity.HasComponent<BoxCollider2DComponent>())
		{
			BoxCollider2DComponent& bc2d = entity.GetComponent<BoxCollider2DComponent>();

			b2ShapeDef shapeDef = b2DefaultShapeDef();
			shapeDef.density = bc2d.Density;
			shapeDef.material.friction = bc2d.Friction;

			b2Polygon polygon = b2MakeOffsetBox(transform.scale.x * bc2d.Size.x, transform.scale.y * bc2d.Size.y, { bc2d.Offset.x, bc2d.Offset.y }, b2Rot_identity);
			b2CreatePolygonShape(rb2d.Box2DBodyID, &shapeDef, &polygon);
		}

	}

	void Scene::EndPhysicsWorld()
	{
		EG_PROFILE_FUNCTION();
		auto view = m_Registry.view<RigidBody2DComponent>();
		for (auto entity : view)
		{
			RigidBody2DComponent& rb2d = view.get<RigidBody2DComponent>(entity);
			b2DestroyBody(rb2d.Box2DBodyID);
			rb2d.Box2DBodyID = b2_nullBodyId;
		}

		b2DestroyWorld(m_Box2dWorldID);
		m_Box2dWorldID = b2_nullWorldId;
	}

	void Scene::SetPrimaryCamera(Entity cameraEntity)
	{
		EG_PROFILE_FUNCTION();
		m_PrimaryCamera = cameraEntity;
	}

}