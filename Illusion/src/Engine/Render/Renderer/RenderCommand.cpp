/*****************************************************************//**
 * \file   RenderCommand.cpp
 * \brief  RenderCommand class, wrapping all basic opengl commands
 * 
 * \author Mian Li
 * \date   January 2023
 *********************************************************************/

#include "pch.h"
#include "RenderCommand.h"

#include <glad/glad.h>

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	void RenderCommand::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	// Set the clear color and clear the color buffer with it
	// Clear the depth buffer at the same time
	void RenderCommand::Clear(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	// Draw stuffs with VBO and IBO
	void RenderCommand::DrawIndexed(const Ref<VAO>& vao, uint32_t indexCount)
	{
		uint32_t count = indexCount ? indexCount: vao->GetIBO()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}


	void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	//--------------------namespace: Illusion ends--------------------
}