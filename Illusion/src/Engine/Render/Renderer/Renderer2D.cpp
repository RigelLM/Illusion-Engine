#include "pch.h"
#include "Renderer2D.h"

#include "Engine/Render/Utils/VertexArray.h"
#include "Engine/Core/Resource/ResourceManager.h"
#include "Engine/Render/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Illusion
{
	struct RendererStorage
	{
		Ref<VAO> vao;
	};

	static RendererStorage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new RendererStorage();

		// Create VAO
		s_Data->vao.reset(new VAO());

		// Set up Vertices
		float squarevertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		// Create VBO with vertices data
		Ref<VBO> squareVBO;
		squareVBO.reset(new VBO(squarevertices, sizeof(squarevertices)));

		// Set up the layout of the vertices data for every vertex
		VBODataLayout squarelayout = {
			{ VertexDataType::Float3, "a_Position" },
			{ VertexDataType::Float2, "v_TextCord" }
		};

		squareVBO->SetDataLayout(squarelayout);

		s_Data->vao->AddVBO(squareVBO);

		// Set up indices
		unsigned int squareindices[6] =
		{
			0,1,2,2,3,0
		};

		// Create IBO/EBO
		Ref<IBO> squareIBO;
		squareIBO.reset(new IBO(squareindices, sizeof(squareindices) / sizeof(uint32_t)));

		// Bind IBO with VAO
		s_Data->vao->SetIBO(squareIBO);

		// Create the shader program
		ResourceManager::LoadShader("assets/shaders/TextureShader.glsl", "TextureShader");
		ResourceManager::LoadShader("assets/shaders/UIShader.glsl", "UIShader");
		ResourceManager::GetShader("TextureShader")->Bind();
		ResourceManager::GetShader("TextureShader")->UploadUniformInt("u_Texture", 0);
		ResourceManager::GetShader("UIShader")->Bind();
		ResourceManager::GetShader("UIShader")->UploadUniformInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const Camera& camera)
	{
		ResourceManager::GetShader("TextureShader")->Bind();
		ResourceManager::GetShader("TextureShader")->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0.0f), size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		ResourceManager::GetShader("TextureShader")->Bind();
		ResourceManager::GetShader("TextureShader")->UploadUniformBool("u_UseTexture", false);

		ResourceManager::GetShader("TextureShader")->UploadUniformFloat4("u_Color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		ResourceManager::GetShader("TextureShader")->UploadUniformMat4("u_Transform", transform);

		s_Data->vao->Bind();
		RenderCommand::DrawIndexed(s_Data->vao);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0.0f), size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		ResourceManager::GetShader("TextureShader")->Bind();
		ResourceManager::GetShader("TextureShader")->UploadUniformBool("u_UseTexture", true);

		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		ResourceManager::GetShader("TextureShader")->UploadUniformMat4("u_Transform", transform);

		s_Data->vao->Bind();
		RenderCommand::DrawIndexed(s_Data->vao);
	}

	void Renderer2D::DrawUIQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		ResourceManager::GetShader("UIShader")->Bind();
		ResourceManager::GetShader("UIShader")->UploadUniformBool("u_UseTexture", true);

		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		ResourceManager::GetShader("UIShader")->UploadUniformMat4("u_Transform", transform);

		s_Data->vao->Bind();
		RenderCommand::DrawIndexed(s_Data->vao);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const glm::vec4& color)
	{
		DrawRotatedQuad(glm::vec3(position.x, position.y, 0.0f), rotation, size, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const glm::vec4& color)
	{
		ResourceManager::GetShader("TextureShader")->Bind();
		ResourceManager::GetShader("TextureShader")->UploadUniformBool("u_UseTexture", false);

		ResourceManager::GetShader("TextureShader")->UploadUniformFloat4("u_Color", color);

		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f });
		glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		glm::mat4 transform = translationMatrix * rotationMatrix * scalingMatrix;

		ResourceManager::GetShader("TextureShader")->UploadUniformMat4("u_Transform", transform);

		s_Data->vao->Bind();
		RenderCommand::DrawIndexed(s_Data->vao);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawRotatedQuad(glm::vec3(position.x, position.y, 0.0f), rotation, size, texture);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		ResourceManager::GetShader("TextureShader")->Bind();
		ResourceManager::GetShader("TextureShader")->UploadUniformBool("u_UseTexture", true);

		texture->Bind();

		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f });
		glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		glm::mat4 transform = translationMatrix * rotationMatrix * scalingMatrix;

		ResourceManager::GetShader("TextureShader")->UploadUniformMat4("u_Transform", transform);

		s_Data->vao->Bind();
		RenderCommand::DrawIndexed(s_Data->vao);
	}

}