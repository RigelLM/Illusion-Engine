#pragma once

#include "Engine/Render/Utils/Texture.h"
#include "Engine/Render/Utils/SubTexture.h"

namespace Illusion
{
	class Renderer2D
	{
	public:

		static void Init();
		static void Shutdown();

		static void Clear(const glm::vec3& color);

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(const glm::mat4& v, const glm::mat4& p);
		static void BeginScene(const glm::mat4& vp);

		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture>& subtexture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture>& subtexture);

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::mat4& transform, const Ref<SubTexture>& subtexture);

		static void DrawUIQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);

		static void DrawRotatedQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawRotatedQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawRotatedQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const Ref<SubTexture>& subtexture);
		static void DrawRotatedQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const Ref<SubTexture>& subtexture);

	private:

		static void Flush();
		static void StartNewBatch();
	};

}