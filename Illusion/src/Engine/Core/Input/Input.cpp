/*
 * ========================== Input.h =================================
 *                              -- ils --
 *                                                 CREATE -- 2023.02.10
 *                                                 MODIFY --
 * --------------------------------------------------------------------
 * Input method implementations
 * ----------------------------
 */

#include "pch.h"
#include "Input.h"

#include "Engine/Core/Application/Application.h"

#include <GLFW/glfw3.h>

 //--------------------namespace: Illusion starts--------------------

namespace Illusion
{

	bool Input::IsKeyPressed(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };

	}

	float Input::GetMouseX()
	{
		auto [x, y] = GetMousePosition();
		return x;
	}

	float Input::GetMouseY()
	{
		auto [x, y] = GetMousePosition();
		return y;
	}
	//--------------------namespace: Illusion ends--------------------
}