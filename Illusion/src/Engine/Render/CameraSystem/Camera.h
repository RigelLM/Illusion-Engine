/*
 * ======================= Camera.h ===========================
 *                       -- ils --
 *                                         CREATE -- 2023.01.16
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The Camera Class
 * ----------------------------
 */

#pragma once

#include <glm/glm.hpp>

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	// The camera class 
	// Containing View Matrix and Projection Matrix
	class Camera
	{
	public:
		// Constructor that take four bound of the projection matrix
		Camera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		void SetPosition(const glm::vec3& position);
		void SetRotation(const float rotation);

		const glm::vec3 GetPosition() const;
		const float GetRotation() const;

		const glm::mat4 GetViewMatrix() const;
		const glm::mat4 GetProjectionMatrix() const;
		const glm::mat4 GetViewProjectionMatrix() const;

	private:

		// Update the viewProjectio matrix everytime when position and rotation is changed
		void UpdateViewProjectionMatrix();

	private:

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };

		float m_Rotation = 0.0f;


	};

	//--------------------namespace: Illusion ends--------------------
}