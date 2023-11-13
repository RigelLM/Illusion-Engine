#pragma once

#include <glm/glm.hpp>

namespace Illusion
{
	class Camera
	{
	public:

		struct OrthographicProperties
		{
			float ZoomLevel = 1.0f;

			float Rotation = 0.0f;

			float Near = -1.0f;
			float Far = 1.0f;
		};

		struct PerspectiveProperties
		{
			glm::vec3 Direction = glm::vec3(0.0f, 0.0f, -1.0f);
			glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

			float FOV = glm::radians(45.0f);

			float Near = 0.1f;
			float Far = 100.0f;
		};

		enum class CameraType { Perspective = 0, Orthographic = 1 };

	public:
		Camera()
		{
			UpdateView();
			UpdateProjection();
		}
		~Camera() = default;

		CameraType GetType() { return m_CameraType; }
		void SetType(CameraType type) { m_CameraType = type; UpdateView(); UpdateProjection(); }

		// Orthographic
		void SetOrthographic(const OrthographicProperties& p) { m_OrthographicProp = p; UpdateView(); UpdateProjection(); }

		const float GetOrthoZoomLevel() { return m_OrthographicProp.ZoomLevel; }
		void SetOrthoZoomLevel(float zl) { m_OrthographicProp.ZoomLevel = zl; UpdateProjection(); }

		const float GetOrthoNear() { return m_OrthographicProp.Near; }
		void SetOrthoNear(float n) { m_OrthographicProp.Near = n; UpdateProjection(); }

		const float GetOrthoFar() { return m_OrthographicProp.Far; }
		void SetOrthoFar(float f) { m_OrthographicProp.Far = f; UpdateProjection(); }

		const float GetOrthoRotation() { return m_OrthographicProp.Rotation; }
		void SetOrthoRotation(float r) { m_OrthographicProp.Rotation = r; UpdateView(); }

		// Perspective
		void SetPerspective(const PerspectiveProperties& p) { m_PerspectiveProp = p; UpdateView(); UpdateProjection(); }

		const float GetPerspectiveFOV() { return m_PerspectiveProp.FOV; }
		void SetPerspectiveFOV(float fov) { m_PerspectiveProp.FOV = fov;  UpdateProjection(); }

		const float GetPerspectiveNear() { return m_PerspectiveProp.Near; }
		void SetPerspectiveNear(float n) { m_PerspectiveProp.Near = n;  UpdateProjection(); }

		const float GetPerspectiveFar() { return m_PerspectiveProp.Far; }
		void SetPerspectiveFar(float f) { m_PerspectiveProp.Far = f; UpdateProjection(); }

		const glm::vec3& GetPerspetiveDirection() { return m_PerspectiveProp.Direction; }
		void SetPerspetiveDirection(const glm::vec3& d) { m_PerspectiveProp.Direction = d; UpdateView(); }

		const glm::vec3& GetPerspetiveUp() { return m_PerspectiveProp.Up; }
		void SetPerspetiveUp(const glm::vec3& u) { m_PerspectiveProp.Up = u; UpdateView(); }

		// General
		const glm::mat4 GetViewProjection() { return m_Projection * m_View; }

		const glm::vec3& GetPosition() { return m_Position; }
		void SetPosition(const glm::vec3& p) { m_Position = p; UpdateView(); }

		float GetAspectRatio() { return m_AspectRatio; }
		void SetAspectRatio(float ar) { m_AspectRatio = ar; UpdateProjection(); }

	private:
		void UpdateView();
		void UpdateProjection();

	private:
		OrthographicProperties m_OrthographicProp;
		PerspectiveProperties m_PerspectiveProp;

		CameraType m_CameraType = CameraType::Orthographic;

		float m_AspectRatio = 800.0f / 600.0f;

		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);

		glm::mat4 m_View;
		glm::mat4 m_Projection;
	};
}

