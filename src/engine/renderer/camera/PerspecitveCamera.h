#pragma once

#include "Camera.h"

namespace Engine {

	class PerspecitveCamera : public Camera
	{
	public:
		PerspecitveCamera(float fov, float aspect);

		void SetProjection(float fov, float aspect);

		const glm::vec3& GetPosition() const { return m_Postion; }
		void SetPosition(const glm::vec3& position) { m_Postion = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(const float& rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		virtual const glm::mat4& GetProjectionMatrix() const override { return m_ProjectionMatrix; }
		virtual const glm::mat4& GetViewMatrix() const override { return m_ViewMatrix; }
		virtual const glm::mat4& GetViewProjectionMatrix() const override { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Postion = glm::vec3(0, 0, 0);
		float m_Rotation = 0.0f;
	};
}

