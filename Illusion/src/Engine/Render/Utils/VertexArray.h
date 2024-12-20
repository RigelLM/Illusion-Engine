#pragma once

/*****************************************************************//**
 * \file   VertexArray.h
 * \brief  VertexArray class, wrapping opengl vertex array obeject
 *
 * \author Mian Li
 * \date   October 2024
 *********************************************************************/

#include <memory>
#include "Buffers.h"

//--------------------namespace: Illusion starts--------------------
namespace Illusion {

	// VAO class
	// Holds the reference to VBOs and IBO
	class VAO
	{
	public:

		VAO();

		~VAO();

		void Bind() const;

		void Unbind() const;

		// Add VBOs to VAO and set vertex attribute pointer according to their layouts
		void AddVBO(const Ref<VBO>& VBO);
		
		// Add IBO to VAO
		void SetIBO(const Ref<IBO>& IBO);

		const std::vector<Ref<VBO>>& GetVBOs() const { return m_VBOs; }
		const Ref<IBO>& GetIBO() const {return m_IBO; }

	private:
		
		std::vector<Ref<VBO>> m_VBOs;

		Ref<IBO> m_IBO;

		uint32_t m_VAO;

		uint32_t m_VBOIndexOffset = 0;
	};
	//--------------------namespace: Illusion ends--------------------
}

