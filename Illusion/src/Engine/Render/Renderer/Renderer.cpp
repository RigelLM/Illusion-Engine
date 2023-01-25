/*
 * ======================= Renderer.cpp =======================
 *                          -- ils --
 *                                         CREATE -- 2023.01.16
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The Renderer Class
 * ----------------------------
 */

#include "pch.h"
#include "Renderer.h"
#include "Renderer2D.h"

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(Camera& camera)
	{
		// Get the ViewProjection Matrix from the camera
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	// Submit the ViewProjection Matrix and VAO to the relevent shader
	// Draw the elements with IBO
	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VAO>& vao, const glm::mat4 transform)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);

		shader->UploadUniformMat4("u_Transform", transform);

		vao->Bind();
		RenderCommand::DrawIndexed(vao);
	}



	//--------------------namespace: Illusion ends--------------------
}