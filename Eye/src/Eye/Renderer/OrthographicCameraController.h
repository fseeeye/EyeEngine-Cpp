#pragma once

#include "Eye/Core/Timestep.h"
#include "Eye/Renderer/OrthographicCamera.h"

#include "Eye/Events/ApplicationEvent.h"
#include "Eye/Events/MouseEvent.h"

namespace Eye {

	/*
	 * @brief Control the Orthographic Camera, specially handle releated events and update camera.
	 */
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool enableRotation = false);

		// Handle Camera transform (View Matrix)
		void OnUpdate(Timestep deltaTime);
		
		// Dispatch events for ortho camera.
		void OnEvent(Event& e);

		inline OrthographicCamera& GetCamera() { return m_Camera; }
		inline const OrthographicCamera& GetCamera() const { return m_Camera; }

		inline float GetZoomLevel() const { return m_ZoomLevel; }
		inline void SetZoomLevel(const float level) { m_ZoomLevel = level; }

	private:
		// Handle mouse scrolled event for updating ortho camera.
		bool OnMouseScrolled(MouseScrolledEvent& e);
		// Handle window resized event for updating ortho camera.
		bool OnWindowResized(WindowResizeEvent& e);

		// Sync info between camera and controller
		inline void UpdateCamera() {
			m_Camera.ResetProjection(-1.f * m_ZoomLevel * m_AspectRaio, 1.f * m_ZoomLevel * m_AspectRaio, -1.f * m_ZoomLevel, 1.f * m_ZoomLevel);
		}

	private:
		float m_AspectRaio;
		float m_ZoomLevel = 1.f;

		OrthographicCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.f, 0.f, 0.f };
		float m_CameraTranslationSpeed = 1.f;

		bool m_EnableCameraRotation;
		float m_CameraRotationAngle = 0.f; //In degrees, in the anti-clockwise direction
		float m_CameraRotationSpeed = 60.f;
	};

}