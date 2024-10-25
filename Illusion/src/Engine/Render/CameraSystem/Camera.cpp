#include "pch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Illusion
{
	void Camera::UpdateProjection()
	{
		if (m_CameraType == CameraType::Perspective)
		{
			m_Projection = glm::perspective(m_PerspectiveProp.FOV, 
				m_AspectRatio, 
				m_PerspectiveProp.Near, 
				m_PerspectiveProp.Far);
		}
		else
		{
			m_Projection = glm::ortho(-m_AspectRatio * m_OrthographicProp.ZoomLevel,
				m_AspectRatio * m_OrthographicProp.ZoomLevel,
				-m_OrthographicProp.ZoomLevel,
				m_OrthographicProp.ZoomLevel,
				m_OrthographicProp.Near,
				m_OrthographicProp.Far);
		}
	}

	void Camera::UpdateView()
	{
		if (m_CameraType == CameraType::Perspective)
		{
			m_View = glm::lookAt(m_Position, m_PerspectiveProp.Direction + m_Position, m_PerspectiveProp.Up);
		}
		else
		{
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
				glm::rotate(glm::mat4(1.0f), glm::radians(m_OrthographicProp.Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

			m_View = glm::inverse(transform);
		}
	}
}
