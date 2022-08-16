#include "eyepch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Eye {

	OrthographicCamera::OrthographicCamera(float zoomLeft, float zoomRight, float zoomBottom, float zoomTop) 
	{
		m_ProjectionMatrix = glm::ortho(zoomLeft, zoomRight, zoomBottom, zoomTop, -1.f, 0.f);
		m_ViewMatrix = glm::mat4(1.f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.f), m_Position);
		transform = glm::rotate(transform, glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::ResetProjection(float zoomLeft, float zoomRight, float zoomBottom, float zoomTop)
	{
		m_ProjectionMatrix = glm::ortho(zoomLeft, zoomRight, zoomBottom, zoomTop, -1.f, 0.f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}