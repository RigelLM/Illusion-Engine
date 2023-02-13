#include "pch.h"
#include "Renderer2D.h"

#include "Engine/Render/Utils/VertexArray.h"
#include "Engine/Core/Resource/ResourceManager.h"
#include "Engine/Render/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Illusion
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
	};
	struct RendererData
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;

		Ref<VAO> vao;
		Ref<VBO> vbo;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 0;
	};

	static RendererData s_Data;

	void Renderer2D::Init()
	{
		// Create VAO
		s_Data.vao.reset(new VAO());

		// Set up Vertices
		// Create VBO with vertices data
		s_Data.vbo.reset(new VBO(s_Data.MaxVertices * sizeof(QuadVertex)));

		// Set up the layout of the vertices data for every vertex
		VBODataLayout quadlayout = {
			{ VertexDataType::Float3, "a_Position" },
			{ VertexDataType::Float4, "a_Color" },
			{ VertexDataType::Float2, "v_TextCord" },
			{ VertexDataType::Float, "a_TexIndex" }
		};

		s_Data.vbo->SetDataLayout(quadlayout);

		s_Data.vao->AddVBO(s_Data.vbo);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];


		// Set up indices
		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		// Create IBO/EBO
		Ref<IBO> squareIBO;
		squareIBO.reset(new IBO(quadIndices, s_Data.MaxIndices));
		// Bind IBO with VAO
		s_Data.vao->SetIBO(squareIBO);
		delete[] quadIndices;




		// Create the shader program
		ResourceManager::LoadShader("assets/shaders/TextureShader.glsl", "TextureShader");

		//------------------------------------------------------------------------//
		ResourceManager::LoadShader("assets/shaders/UIShader.glsl", "UIShader");
		//------------------------------------------------------------------------//

		int samplers[s_Data.MaxTextureSlots];
		for (int i = 0; i < 32; i++)
			samplers[i] = i;

		ResourceManager::GetShader("TextureShader")->Bind();
		ResourceManager::GetShader("TextureShader")->UploadUniformIntArray("u_Texture", samplers, s_Data.MaxTextureSlots);

		//-----------------------------------------------------------------------//
		ResourceManager::GetShader("UIShader")->Bind();
		ResourceManager::GetShader("UIShader")->UploadUniformInt("u_Texture", 0);
		//----------------------------------------------------------------------//
	}

	void Renderer2D::Shutdown()
	{
	}

	void Renderer2D::BeginScene(const Camera& camera)
	{
		ResourceManager::GetShader("TextureShader")->Bind();
		ResourceManager::GetShader("TextureShader")->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 0;
	}

	void Renderer2D::EndScene()
	{
		uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;

		s_Data.vbo->SendData(s_Data.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		// Bind Textures
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
			s_Data.TextureSlots[i]->Bind(i);

		RenderCommand::DrawIndexed(s_Data.vao, s_Data.QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0.0f), size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		ResourceManager::GetShader("TextureShader")->Bind();
		ResourceManager::GetShader("TextureShader")->UploadUniformBool("u_UseTexture", false);

		s_Data.QuadVertexBufferPtr->Position = position;
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = 0.0f;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = 0.0f;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = 0.0f;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = 0.0f;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;

		//ResourceManager::GetShader("TextureShader")->Bind();
		//ResourceManager::GetShader("TextureShader")->UploadUniformBool("u_UseTexture", false);

		//ResourceManager::GetShader("TextureShader")->UploadUniformFloat4("u_Color", color);

		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		//ResourceManager::GetShader("TextureShader")->UploadUniformMat4("u_Transform", transform);

		//s_Data.vao->Bind();
		//RenderCommand::DrawIndexed(s_Data.vao);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0.0f), size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		ResourceManager::GetShader("TextureShader")->Bind();
		ResourceManager::GetShader("TextureShader")->UploadUniformBool("u_UseTexture", true);

		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		float textureIndex = 0.0f;
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}
		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		s_Data.QuadVertexBufferPtr->Position = position;
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;

		//texture->Bind();

		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		//ResourceManager::GetShader("TextureShader")->UploadUniformMat4("u_Transform", transform);

		//s_Data.vao->Bind();
		//RenderCommand::DrawIndexed(s_Data.vao);
	}


	//--------------------------------------------------------------------------------------------------------------------//
	void Renderer2D::DrawUIQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		ResourceManager::GetShader("UIShader")->Bind();
		ResourceManager::GetShader("UIShader")->UploadUniformBool("u_UseTexture", true);

		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		ResourceManager::GetShader("UIShader")->UploadUniformMat4("u_Transform", transform);

		s_Data.vao->Bind();
		RenderCommand::DrawIndexed(s_Data.vao);
	}
	//--------------------------------------------------------------------------------------------------------------------//


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

		s_Data.vao->Bind();
		RenderCommand::DrawIndexed(s_Data.vao);
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

		s_Data.vao->Bind();
		RenderCommand::DrawIndexed(s_Data.vao);
	}

}