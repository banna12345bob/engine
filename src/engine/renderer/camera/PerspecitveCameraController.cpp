#include "PerspecitveCameraController.h"

namespace Engine {

	PerspecitveCameraController::PerspecitveCameraController(float aspectratio, glm::vec3 position)
		: m_AspectRatio(aspectratio), m_Camera(35.f, m_AspectRatio), m_CameraPosition(-position)
	{
		EG_CORE_WARN("Perspective Camera not implimented correctly yet");
		m_Camera.nearClipping = -10.f;
		m_Camera.farClipping = 10.f;
	}

	void PerspecitveCameraController::OnUpdate(Timestep ts)
	{
		m_Camera.SetPosition(m_CameraPosition);
	}

	void PerspecitveCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(EG_BIND_EVENT_FN(PerspecitveCameraController::OnWindowRezise));
	}

	void PerspecitveCameraController::CaculateView()
	{
		m_Camera.SetProjection(m_CameraFOV, m_AspectRatio);
	}

	bool PerspecitveCameraController::OnWindowRezise(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		CaculateView();
		return false;
	}
}