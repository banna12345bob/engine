#include "Entity.h"
#include "Scene.h"

#include "engine/renderer/Renderer2D.h"

namespace Engine {

	Entity::Entity(std::string name, Scene& scene)
	: name(name), m_Scene(scene)
	{
		TransformComponent* transformComponent = new TransformComponent();
		SpriteRendererComponent* spriteRendererComponent = new SpriteRendererComponent();
		VelocityComponent* accelerationComponent = new VelocityComponent();

		m_Components[Components::Transform] = transformComponent;
		m_Components[Components::SpriteRenderer] = spriteRendererComponent;
		m_Components[Components::Velocity] = accelerationComponent;

		// Default, size of one tile
		m_BoundingBox = BoundingBox(-8, -8, 16, 16);
	}

	void Entity::OnUpdate(Timestep ts)
	{
		
		GetTransform()->rotation += GetVelocity()->rotationVelocity * ts.GetSeconds();
		GetTransform()->scale += GetVelocity()->scaleVelocity * ts.GetSeconds();

		// Check for collisions (does not account for scale)
		BoundingBox box = GetBoundingBox(GetTransform()->position);
		glm::vec2 displacement = glm::vec2(GetVelocity()->velocity.x * ts.GetSeconds(), GetVelocity()->velocity.y * ts.GetSeconds());
		glm::vec2 actualDisplacement;
		m_Scene.CheckCollisions(box, displacement, actualDisplacement);
		GetTransform()->position += glm::vec3(actualDisplacement.x, actualDisplacement.y, 0);

		// See if velocity needs to be reset
		if (displacement.x != actualDisplacement.x) {
			GetVelocity()->velocity.x = 0;
		}
		if (displacement.y != actualDisplacement.y) {
			GetVelocity()->velocity.y = 0;
		}

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

	void Entity::Move(glm::vec2 dir, int acceleration, int maxSpeed, Timestep ts) {

		// X axis
		if ((dir.x != 0 && GetVelocity()->velocity.x == 0) || dir.x * GetVelocity()->velocity.x > 0) {	// Same direction or just started moving
			if (abs(GetVelocity()->velocity.x) < maxSpeed * abs(dir.x)) {
				GetVelocity()->velocity.x += acceleration * dir.x * ts;
			}
			else {
				GetVelocity()->velocity.x = maxSpeed * dir.x;
			}
		}
		else if (dir.x == 0) {																			// Not moving on this axis
			if (GetVelocity()->velocity.x != 0) {														// Need to decelerate
				int sign = (GetVelocity()->velocity.x > 0) - (GetVelocity()->velocity.x < 0);			// Hack I found on Stack Overflow
				GetVelocity()->velocity.x += acceleration * ts * -sign * 2.f;							// Decelerate faster than accelerate
				if (GetVelocity()->velocity.x * sign < 0) {												// If we have gone past 0, set it to 0
					GetVelocity()->velocity.x = 0;
				}
			}
		}
		else {																							// Going in opposite direction
			GetVelocity()->velocity.x = acceleration * dir.x * ts;
		}

		// Y axis
		if ((dir.y != 0 && GetVelocity()->velocity.y == 0) || dir.y * GetVelocity()->velocity.y > 0) {
			if (abs(GetVelocity()->velocity.y) < maxSpeed * abs(dir.y)) {
				GetVelocity()->velocity.y += acceleration * dir.y * ts;
			}
			else {
				GetVelocity()->velocity.y = maxSpeed * dir.y;
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

	BoundingBox Entity::GetBoundingBox(glm::vec2 pos) {
		return BoundingBox(pos.x + m_BoundingBox.x, pos.y + m_BoundingBox.y, m_BoundingBox.width, m_BoundingBox.height);
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