#include "Entity.h"

#include "engine/renderer/Renderer2D.h"

namespace Engine {

	Entity::Entity(std::string name)
	: name(name)
	{
		TransformComponent* transformComponent = new TransformComponent();
		SpriteRendererComponent* spriteRendererComponent = new SpriteRendererComponent();

		m_Components.push_back(transformComponent);
		m_Components.push_back(spriteRendererComponent);
	}

	void Entity::Render()
	{
		if (((SpriteRendererComponent*)m_Components[1])->texture)
		{
			Renderer2D::DrawQuad(((TransformComponent*)m_Components[0])->position, ((TransformComponent*)m_Components[0])->scale, ((TransformComponent*)m_Components[0])->rotation, ((SpriteRendererComponent*)m_Components[1])->texture, ((SpriteRendererComponent*)m_Components[1])->colour, ((SpriteRendererComponent*)m_Components[1])->tilingFactor);
		} else {
			Renderer2D::DrawQuad(((TransformComponent*)m_Components[0])->position, ((TransformComponent*)m_Components[0])->scale, ((TransformComponent*)m_Components[0])->rotation, ((SpriteRendererComponent*)m_Components[1])->colour);
		}
	}

	TransformComponent* Entity::GetTransform()
	{
		return ((TransformComponent*)m_Components[0]);
	}

	SpriteRendererComponent* Entity::GetSpriteRenderer()
	{
		return ((SpriteRendererComponent*)m_Components[1]);
	}
}