#include "PerspecitveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine {
		PerspecitveCamera::PerspecitveCamera(float fov, float aspect)
		:m_ViewMatrix(1.0f)
	{
		SetProjection(fov, aspect);
	}

	void PerspecitveCamera::SetProjection(float fov, float aspect)
	{
		m_ProjectionMatrix = glm::perspective(fov, aspect, nearClipping, farClipping);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspecitveCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Postion) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = transform;
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
