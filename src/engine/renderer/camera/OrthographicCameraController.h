#pragma once

#include "engine/renderer/camera/OrthographicCamera.h"

#include "engine/core/Timestep.h"
#include "engine/events/AllEvents.h"

namespace Engine {

	struct OrthographicCameraBounds
	{
		float Left, Right;
		float Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectratio, glm::vec3 position = { 0.0f, 0.0f, 0.0f }, bool canMove = false, bool canZoom = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; CaculateView(); }

		const OrthographicCameraBounds& getBounds() const { return m_Bounds; }

		// Sets the position of the camera 
		void setPosition(const glm::vec3 position) { m_CameraPosition = position; }
		const glm::vec3& getPosition() const { return m_CameraPosition; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowRezise(WindowResizeEvent& e);

		void CaculateView();
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;
		OrthographicCameraBounds m_Bounds;

		bool m_enableWASD, m_enableScroll;
		float m_CameraTranslationSpeed = 1.0f;

		glm::vec3 m_CameraPosition;
	};
}

