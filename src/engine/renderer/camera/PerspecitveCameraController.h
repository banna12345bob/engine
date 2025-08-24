#pragma once

#include "engine/renderer/camera/PerspecitveCamera.h"

#include "engine/core/Timestep.h"
#include "engine/events/AllEvents.h"

namespace Engine {

	class PerspecitveCameraController
	{
	public:
		PerspecitveCameraController(float aspectratio, glm::vec3 position = { 0.0f, 0.0f, 0.0f });

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		PerspecitveCamera& GetCamera() { return m_Camera; }
		const PerspecitveCamera& GetCamera() const { return m_Camera; }

		float GetCameraFOV() const { return m_CameraFOV; }
		void SetCameraFOV(float fov) { m_CameraFOV = fov; CaculateView(); }

		// Sets the position of the camera 
		void setPosition(const glm::vec3 position) { m_CameraPosition = position; }
		const glm::vec3& getPosition() const { return m_CameraPosition; }
	private:
		bool OnWindowRezise(WindowResizeEvent& e);

		void CaculateView();
	private:
		float m_AspectRatio;
		float m_CameraFOV = 1.0f;
		PerspecitveCamera m_Camera;

		glm::vec3 m_CameraPosition;
	};
}

