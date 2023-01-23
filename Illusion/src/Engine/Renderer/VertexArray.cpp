/*
 * ===================== VertexArray.cpp ======================
 *                          -- ils --
 *                                         CREATE -- 2023.01.16
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The VAO class
 * ----------------------------
 */

#include "pch.h"
#include "VertexArray.h"

#include <glad/glad.h>

 //--------------------namespace: Illusion starts--------------------
namespace Illusion {
	
	// Helper functon that cast the vertex datatype to opengl base tyep
	static GLenum VertexDataTypetoOpenGLBaseType(VertexDataType type)
	{
		switch (type)
		{
		case Illusion::VertexDataType::Float:		return GL_FLOAT;
		case Illusion::VertexDataType::Float2:		return GL_FLOAT;
		case Illusion::VertexDataType::Float3:		return GL_FLOAT;
		case Illusion::VertexDataType::Float4:		return GL_FLOAT;
		case Illusion::VertexDataType::Mat3:		return GL_FLOAT;
		case Illusion::VertexDataType::Mat4:		return GL_FLOAT;
		case Illusion::VertexDataType::Int:			return GL_INT;
		case Illusion::VertexDataType::Int2:		return GL_INT;
		case Illusion::VertexDataType::Int3:		return GL_INT;
		case Illusion::VertexDataType::Int4:		return GL_INT;
		case Illusion::VertexDataType::Bool:		return GL_BOOL;
		}
	}

	// Constructor
	VAO::VAO()
	{
		glCreateVertexArrays(1, &m_VAO);

	}

	VAO::~VAO()
	{
		glDeleteVertexArrays(1, &m_VAO);
	}

	void VAO::Bind() const
	{
		glBindVertexArray(m_VAO);
	}

	void VAO::Unbind() const
	{
		glBindVertexArray(0);
	}

	// Add VBOs to VAO and set vertex attribute pointer according to their layouts
	void VAO::AddVBO(const Ref<VBO>& VBO)
	{
		ILLUSION_CORE_ASSERT(VBO->GetDataLayout().GetVertexData().size(), "VBO has no layout!");

		glBindVertexArray(m_VAO);
		VBO->Bind();

		// Set up the Vertex Attribute Pointer for each element in the vertices data of VBO
		uint32_t index = 0;
		const auto& layout = VBO->GetDataLayout();
		for (const auto& vertexdata : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				vertexdata.GetComponentCount(),
				VertexDataTypetoOpenGLBaseType(vertexdata.Type),
				vertexdata.Normalized,
				layout.GetStride(),
				(const void*)vertexdata.Offset);
			index++;
		}

		m_VBOs.push_back(VBO);
	}

	// Add IBO to VAO
	void VAO::SetIBO(const Ref<IBO>& IBO)
	{
		glBindVertexArray(m_VAO);
		IBO->Bind();

		m_IBO = IBO;
	}
	//--------------------namespace: Illusion ends--------------------
}