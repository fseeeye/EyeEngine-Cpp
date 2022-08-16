#include "eyepch.h"
#include "OrthographicCameraController.h"

#include "Eye/input.h"
#include "Eye/KeyCodes.h"
#include "Eye/Core.h"

namespace Eye {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool enableRotation /*= false*/)
		: m_AspectRaio(aspectRatio)
		, m_EnableCameraRotation(enableRotation)
		, m_Camera(-1.f * m_ZoomLevel * aspectRatio, 1.f * m_ZoomLevel * aspectRatio, -1.f * m_ZoomLevel, 1.f * m_ZoomLevel)
	{}

	void OrthographicCameraController::OnUpdate(Timestep deltaTime)
	{
		// handle translation
		if (Input::IsKeyPressed(EYE_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * deltaTime;
		else if (Input::IsKeyPressed(EYE_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * deltaTime;

		if (Input::IsKeyPressed(EYE_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * deltaTime;
		else if (Input::IsKeyPressed(EYE_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * deltaTime;

		// handle rotation
		if (m_EnableCameraRotation)
		{
			if (Input::IsKeyPressed(EYE_KEY_Q))
				m_CameraRotationAngle += m_CameraRotationSpeed * deltaTime;
			else if (Input::IsKeyPressed(EYE_KEY_E))
				m_CameraRotationAngle -= m_CameraRotationSpeed * deltaTime;
			
			m_Camera.SetRotation(m_CameraRotationAngle);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(EYE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(EYE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= static_cast<float>(e.GetYOffset());
		UpdateCamera();

		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRaio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
		UpdateCamera();
		
		return false;
	}

}