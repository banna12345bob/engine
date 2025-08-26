#include "Entity.h"

#include "engine/renderer/Renderer2D.h"

namespace Engine {

	Entity::Entity(std::string name)
	: name(name)
	{
		TransformComponent* transformComponent = new TransformComponent();
		SpriteRendererComponent* spriteRendererComponent = new SpriteRendererComponent();
		VelocityComponent* accelerationComponent = new VelocityComponent();

		m_Components[Components::Transform] = transformComponent;
		m_Components[Components::SpriteRenderer] = spriteRendererComponent;
		m_Components[Components::Velocity] = accelerationComponent;
	}

	void Entity::OnUpdate(Timestep ts)
	{
		GetTransform()->position += GetVelocity()->velocity * ts.GetSeconds();
		GetTransform()->rotation += GetVelocity()->rotationVelocity * ts.GetSeconds();
		GetTransform()->scale += GetVelocity()->scaleAcceleration * ts.GetSeconds();
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

	VelocityComponent* Entity::GetVelocity()
	{
		return ((VelocityComponent*)m_Components[Components::Velocity]);
	}
}