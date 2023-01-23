/*
 * ===================== GraphicContext.cpp ====================
 *                         -- ils --
 *                                         CREATE -- 2023.01.16
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The GraphicContext Class
 * ----------------------------
 */

#include "pch.h"

#include "GraphicContext.h"

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{

	GraphicContext::GraphicContext(GLFWwindow* WindowHandle)
		: m_WindowHandle(WindowHandle)
	{
		ILLUSION_CORE_ASSERT(WindowHandle, "Window handle is Null!");
	}

	void GraphicContext::Init()
	{
		// Set a glfwwindow as the context
		// One thread could only have one context
		glfwMakeContextCurrent(m_WindowHandle);

		// Check if glad has been initialized
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ILLUSION_CORE_ASSERT(status, "Failed to initialize Glad!");

		// Log the OpenGL information to the console
		ENGINE_CORE_INFO("OpenGL Info:");
		ENGINE_CORE_INFO("  Vendor\t: {0}", glGetString(GL_VENDOR));
		ENGINE_CORE_INFO("  Renderer\t: {0}", glGetString(GL_RENDERER));
		ENGINE_CORE_INFO("  Version\t: {0}", glGetString(GL_VERSION));

	}

	// Swap the framebuffer
	void GraphicContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
	//--------------------namespace: Illusion ends--------------------
}