/*
 * ====================== Texture.h =====================
 *                       -- ils --
 *                                   CREATE -- 2023.01.20
 *                                   MODIFY --
 * ------------------------------------------------------
 * The Abstract Texture Class
 * The Texure2D Class which will be used in application
 * ----------------------------
 */
#pragma once

#include "Engine/Core/Core.h"

#include <string>

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	// The abstract texture class
	class Texture
	{
	public:

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot) const = 0;
		virtual void Unbind() const = 0;
	};

	// The Texture2D Class which would be used in application
	class Texture2D : public Texture
	{
	public: 
		
		// Generate the 2D texture from the source file
		Texture2D(const std::string& path);
		// Generate the 2D texture in GPU
		Texture2D(uint32_t width, uint32_t height);

		~Texture2D();

		void SetData(const void* data, uint32_t size);

		uint32_t GetWidth() const override { return m_Width; }
		uint32_t GetHeight() const override { return m_Height; }

		// Bind the texture to the texture unit
		void Bind(uint32_t slot = 0) const override;
		void Unbind() const override;

	private:

		// Store the source file path
		std::string m_Path;

		// Store the width and height of the texture
		uint32_t m_Width;
		uint32_t m_Height;

		// Store the rendererID
		uint32_t m_RendererID;
	};



	//--------------------namespace: Illusion ends--------------------
}

