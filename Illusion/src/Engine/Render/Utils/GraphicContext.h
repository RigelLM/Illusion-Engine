/*
 * ===================== GraphicContext.h ======================
 *                         -- ils --
 *                                         CREATE -- 2023.01.16
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The GraphicContext Class
 * Sets up glfw context
 * ----------------------------
 */

#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	// The GraphicContext Class
	class GraphicContext
	{
	public :

		GraphicContext(GLFWwindow* WindowHandle);

		void Init();
		void SwapBuffers();

	private:

		GLFWwindow* m_WindowHandle;

	};


	//--------------------namespace: Illusion ends--------------------
}