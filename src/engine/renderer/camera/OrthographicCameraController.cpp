#include "OrthographicCameraController.h"

namespace Engine {

	OrthographicCameraController::OrthographicCameraController(float aspectratio, glm::vec3 position)
		: m_AspectRatio(aspectratio), m_Bounds({ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel }), m_Camera(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top), m_CameraPosition(-position)
	{

	}

	void OrthographicCameraController::OnUpdate()
	{
		m_Camera.SetPosition(m_CameraPosition);
	}

	void OrthographicCameraController::CaculateView()
	{
		m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
		m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
	}

}