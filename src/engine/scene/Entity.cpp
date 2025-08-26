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
		GetTransform()->scale += GetVelocity()->scaleVelocity * ts.GetSeconds();
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

	// After writing this, I realised it is probably better to do all calculations with a normalised vector then multiply by max speed at the end, but I won't be changing it now
	void Entity::Move(glm::vec2 dir, int acceleration, int entityMaxSpeed, Timestep ts) {

		// If the player is moving diagonally, the max speed on either axis is / root 2
		float maxSpeed = dir.x != 0 && dir.y != 0 ? entityMaxSpeed * 0.707f: entityMaxSpeed;

		// X axis
		if ((dir.x != 0 && GetVelocity()->velocity.x == 0) || dir.x * GetVelocity()->velocity.x > 0) {	// Same direction or just started moving
			if (abs(GetVelocity()->velocity.x) < maxSpeed) {
				GetVelocity()->velocity.x += acceleration * dir.x * ts;
			}
		}
		else if (dir.x == 0) {																					// Not moving on this axis
			if (GetVelocity()->velocity.x != 0) {														// Need to decelerate
				int sign = (GetVelocity()->velocity.x > 0) - (GetVelocity()->velocity.x < 0);	// Hack I found on Stack Overflow
				GetVelocity()->velocity.x += acceleration * ts * -sign;
				if (GetVelocity()->velocity.x * sign < 0) {												// If we have gone past 0, set it to 0
					GetVelocity()->velocity.x = 0;
				}
			}
		}
		else {																									// Going in opposite direction
			GetVelocity()->velocity.x = acceleration * dir.x * ts;
		}

		// Y axis
		if ((dir.y != 0 && GetVelocity()->velocity.y == 0) || dir.y * GetVelocity()->velocity.y > 0) {
			if (abs(GetVelocity()->velocity.y) < maxSpeed) {
				GetVelocity()->velocity.y += acceleration * dir.y * ts;
			}
		}
		else if (dir.y == 0) {
			if (GetVelocity()->velocity.y != 0) {
				int sign = (GetVelocity()->velocity.y > 0) - (GetVelocity()->velocity.y < 0);
				GetVelocity()->velocity.y += acceleration * ts * -sign;
				if (GetVelocity()->velocity.y * sign < 0) {
					GetVelocity()->velocity.y = 0;
				}
			}
		}
		else {
			GetVelocity()->velocity.y = acceleration * dir.y * ts;
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