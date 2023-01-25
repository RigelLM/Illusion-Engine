/*
 * ======================= Renderer.h =========================
 *                          -- ils --
 *                                         CREATE -- 2023.01.16
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The Renderer Class
 * A static class but holds the data of the scene in the game
 * ----------------------------
 */

#pragma once
 
#include "RenderCommand.h"
#include "Engine/Render/CameraSystem/Camera.h"
#include "Engine/Render/Utils/Shader.h"

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	// The Renderer Class
	class Renderer
	{
	public:
		static void Init();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(Camera& camera);
		static void EndScene();

		// Submit the ViewProjection Matrix and VAO to the relevent shader
		static void Submit(const Ref<Shader>& shader, const Ref<VAO>& vao, const glm::mat4 transform = glm::mat4(1.0f));

	private:

		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};


	//--------------------namespace: Illusion ends--------------------
}

