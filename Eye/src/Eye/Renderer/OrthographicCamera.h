#pragma once

#include <glm/glm.hpp>

namespace Eye {

	class OrthographicCamera // 2D Camera
	{
	public:
		OrthographicCamera(float zoomLeft, float zoomRight, float zoomBottom, float zoomTop);

		void ResetProjection(float zoomLeft, float zoomRight, float zoomBottom, float zoomTop);

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		inline float GetRotation() const { return m_Rotation; }
		inline void SetRotation(float angle) { m_Rotation = angle; RecalculateViewMatrix(); }

		inline const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		inline const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix; // P Matrix
		glm::mat4 m_ViewMatrix; // V Matrix
		glm::mat4 m_ViewProjectionMatrix; // VP Matrix

		glm::vec3 m_Position = { 0.f, 0.f, 0.f };
		float m_Rotation = 0.f;
	};

}