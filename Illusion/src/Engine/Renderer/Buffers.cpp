/*
 * ===================== Buffers.cpp ==========================
 *                       -- ils --
 *                                         CREATE -- 2023.01.14
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The buffer classes
 * VBO and EBO
 * ----------------------------
 */

#include "pch.h"
#include "Buffers.h"

#include <glad/glad.h>


 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{	
	//--------------------Vertex Buffer--------------------
	//------------------------ VBO ------------------------
	VBO::VBO(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	VBO::~VBO()
	{
		glDeleteBuffers(1, &m_VBO);
	}

	void VBO::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	}

	void VBO::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//--------------------Index Buffer---------------------
	//------------------------ EBO ------------------------

	IBO::IBO(uint32_t* indices, uint32_t count)
		:m_Count(count)
	{
		glCreateBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}

	IBO::~IBO()
	{
		glDeleteBuffers(1, &m_IBO);

	}
	void IBO::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	}

	void IBO::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	//--------------------namespace: Illusion ends--------------------
}