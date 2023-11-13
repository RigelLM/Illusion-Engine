#pragma once

#include <glm/glm.hpp>

#include "Texture.h"

namespace Illusion {

	class SubTexture
	{
	public:

		SubTexture(const Ref<Texture2D>& spritesheet, const glm::vec2& min, const glm::vec2& max);

		const glm::vec2* GetTexCoords() const { return m_TexCoords; }
		const Ref<Texture2D> GetSpriteSheet() const { return m_SpriteSheet; }
		
		static Ref<SubTexture> CreateFromCoords(const Ref<Texture2D>& spritesheet, const glm::vec2& coords, const glm::vec2& cellsize, const glm::vec2& spritesize = { 1 , 1 });

	private:

		Ref<Texture2D> m_SpriteSheet;

		glm::vec2 m_TexCoords[4];

	};

}

