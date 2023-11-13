#include "pch.h"
#include "SubTexture.h"

namespace Illusion
{
	SubTexture::SubTexture(const Ref<Texture2D>& spritesheet, const glm::vec2& min, const glm::vec2& max)
		:m_SpriteSheet(spritesheet)
	{
		m_TexCoords[0] = { min.x, min.y };
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };
	}

	Ref<SubTexture> SubTexture::CreateFromCoords(const Ref<Texture2D>& spritesheet, const glm::vec2& coords, const glm::vec2& cellsize, const glm::vec2& spritesize)
	{
		glm::vec2 min = { (coords.x * cellsize.x) / spritesheet->GetWidth(), (coords.y * cellsize.y) / spritesheet->GetHeight() };
		glm::vec2 max = { ((coords.x + spritesize.x) * cellsize.x) / spritesheet->GetWidth(), ((coords.y + spritesize.y) * cellsize.y) / spritesheet->GetHeight() };

		return CreateRef<SubTexture>(spritesheet, min, max);
	}
}
