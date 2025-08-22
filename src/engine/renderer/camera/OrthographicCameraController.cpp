#include "OrthographicCameraController.h"

namespace Engine {

	OrthographicCameraController::OrthographicCameraController(float aspectratio, glm::vec3 position)
		: m_AspectRatio(aspectratio), m_Bounds({ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel }), m_Camera(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top), m_CameraPosition(-position)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		m_Camera.SetPosition(m_CameraPosition);
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(EG_BIND_EVENT_FN(OrthographicCameraController::OnWindowRezise));
	}

	void OrthographicCameraController::CaculateView()
	{
		m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
		m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
	}

	bool OrthographicCameraController::OnWindowRezise(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		CaculateView();
		return false;
	}
}