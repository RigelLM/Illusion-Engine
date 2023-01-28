/*
 * ===================== Texture.cpp ====================
 *                       -- ils --
 *                                   CREATE -- 2023.01.20
 *                                   MODIFY --
 * ------------------------------------------------------
 * The Texture Class
 * ----------------------------
 */

#include "pch.h"
#include "Texture.h"

#include <stb_image.h>

#include <glad/glad.h>

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	// Generate the 2D texture from the source file
	Texture2D::Texture2D(const std::string& path)
		:m_Path(path)
	{
		int width, height, channels;

		// Reverse the texture so the stbi axis directions would max with opengl axis directions
		stbi_set_flip_vertically_on_load(1);

		// Read the texture from the file
		stbi_uc* data = stbi_load(m_Path.c_str(), &width, &height, &channels, 0);
		ILLUSION_CORE_ASSERT(data, "Failed to load texture !");
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		// Check whether the texture support alpha channel
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if(channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		ILLUSION_CORE_ASSERT(internalFormat & dataFormat, "Format do not support!");

		// Create the teture
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		// Set the filter mode of the texture when it is scaled
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		// Free the data when it is no longer used
		stbi_image_free(data);
	}

	// Generate the 2D texture in GPU
	Texture2D::Texture2D(uint32_t width, uint32_t height)
		:m_Width(width), m_Height(height)
	{
		GLenum internalFormat = GL_RGBA8, dataFormat = GL_RGBA;

		// Create the teture
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		// Set the filter mode of the texture when it is scaled
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	void Texture2D::SetData(const void* data, uint32_t size)
	{
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_INT, data);
	}


	// Free the data when it is no longer used
	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	// Bind the texture to the texture unit
	void Texture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

	void Texture2D::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	//--------------------namespace: Illusion ends--------------------
}
