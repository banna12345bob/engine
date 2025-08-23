#include "OrthographicCameraController.h"

#include "engine/core/Keycodes.h"
#include "engine/events/Input.h"

namespace Engine {

	OrthographicCameraController::OrthographicCameraController(float aspectratio, glm::vec3 position, bool canMove, bool canZoom)
		: m_AspectRatio(aspectratio), m_Bounds({ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel }), m_Camera(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top), m_CameraPosition(-position), m_enableWASD(canMove), m_enableScroll(canZoom)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (m_enableWASD)
		{
			if (Input::IsKeyPressed(EG_KEY_D))
			{
				m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
			}

			else if (Input::IsKeyPressed(EG_KEY_A))
			{
				m_CameraPosition.x += m_CameraTranslationSpeed * ts;
			}


			if (Input::IsKeyPressed(EG_KEY_S))
			{
				m_CameraPosition.y += m_CameraTranslationSpeed * ts;
			}


			else if (Input::IsKeyPressed(EG_KEY_W))
			{
				m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
			}
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(EG_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(EG_BIND_EVENT_FN(OrthographicCameraController::OnWindowRezise));
	}

	void OrthographicCameraController::CaculateView()
	{
		m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
		m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		if (m_enableScroll)
		{
			m_ZoomLevel -= e.GetYOffset();
			m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
			CaculateView();
			return false;
		}
		return false;
	}

	bool OrthographicCameraController::OnWindowRezise(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		CaculateView();
		return false;
	}
}