/*
 * ======================= CameraController.h ===========================
 *								-- ils --
 *													CREATE -- 2023.01.20
 *													MODIFY --
 * ---------------------------------------------------------------------
 * The CameraController Class
 * Provide functions to controll the camera
 * The wrapper class of camera
 * ----------------------------
 */

 //--------------------namespace: Illusion starts--------------------
#pragma once
#include "Camera.h"
#include "Engine/Core/Utils/Timestep.h"

#include "Engine/Event/AppEvent.h"
#include "Engine/Event/MouseEvent.h"

namespace Illusion
{
	struct CameraBounds
	{
		float Left, Right;
		float Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};

	// The CameraController Class
	class CameraController
	{

	public:

		CameraController(float aspectRatio, bool allowrotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		// Expose the camera
		Camera& GetCamera() { return m_Camera; }
		const Camera& GetCamera() const { return m_Camera; }
		const CameraBounds& GetBounds() const { return m_Bounds; }

	private:
		
		// Callback functions for mouse scolled event and window resized event
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:

		// The viewport ratio
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;

		// must be initialized after m_AspectRation and m_ZoomLevel since it needs these two values to be initialized
		Camera m_Camera;
		CameraBounds m_Bounds;

		// Check whether the rotation method is enabled
		bool m_AllowRotation;

		// Store the camera's position and rotation
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0;

		// The moving speed of camera
		float m_CameraTranslationSpeed = 1.0f;
		float m_CameraRotationSpeed = 180.0f;
	};
	//--------------------namespace: Illusion ends--------------------
}


