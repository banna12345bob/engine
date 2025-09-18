#include "Entity.h"
#include "Scene.h"

#include "engine/renderer/Renderer2D.h"

namespace Engine {

	Entity::Entity(entt::entity handler, Scene* scene)
	: m_EntityHandler(handler), m_Scene(scene)
	{
	}

}