#include "Entity.h"

#include "engine/renderer/Renderer2D.h"

namespace Engine {

	Entity::Entity(std::string name)
	: name(name)
	{
		TransformComponent* transformComponent = new TransformComponent();
		SpriteRendererComponent* spriteRendererComponent = new SpriteRendererComponent();
		AccelerationComponent* accelerationComponent = new AccelerationComponent();

		m_Components[Components::Transform] = transformComponent;
		m_Components[Components::SpriteRenderer] = spriteRendererComponent;
		m_Components[Components::Acceleration] = accelerationComponent;
	}

	void Entity::OnUpdate(Timestep ts)
	{
		GetTransform()->position += GetAcceleration()->acceleration * ts.GetSeconds();
		GetTransform()->rotation += GetAcceleration()->rotationAcceleration * ts.GetSeconds();
		GetTransform()->scale += GetAcceleration()->scaleAcceleration * ts.GetSeconds();
	}

	void Entity::OnRender()
	{
		if (((SpriteRendererComponent*)m_Components[Components::SpriteRenderer])->texture)
		{
			Renderer2D::DrawQuad(((TransformComponent*)m_Components[Components::Transform])->position, ((TransformComponent*)m_Components[Components::Transform])->scale, ((TransformComponent*)m_Components[Components::Transform])->rotation, ((SpriteRendererComponent*)m_Components[Components::SpriteRenderer])->texture, ((SpriteRendererComponent*)m_Components[Components::SpriteRenderer])->colour, ((SpriteRendererComponent*)m_Components[Components::SpriteRenderer])->tilingFactor);
		} else {
			Renderer2D::DrawQuad(((TransformComponent*)m_Components[Components::Transform])->position, ((TransformComponent*)m_Components[Components::Transform])->scale, ((TransformComponent*)m_Components[Components::Transform])->rotation, ((SpriteRendererComponent*)m_Components[Components::SpriteRenderer])->colour);
		}
	}

	TransformComponent* Entity::GetTransform()
	{
		return ((TransformComponent*)m_Components[Components::Transform]);
	}

	SpriteRendererComponent* Entity::GetSpriteRenderer()
	{
		return ((SpriteRendererComponent*)m_Components[Components::SpriteRenderer]);
	}

	AccelerationComponent* Entity::GetAcceleration()
	{
		return ((AccelerationComponent*)m_Components[Components::Acceleration]);
	}
}