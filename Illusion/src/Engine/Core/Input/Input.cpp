/*****************************************************************//**
 * \file   Input.cpp
 * \brief  Input method implementation
 * 
 * \author Mian Li
 * \date   Febuary 2023
 *********************************************************************/


#include "pch.h"
#include "Input.h"

#include "Engine/Core/Application/Application.h"

#include <GLFW/glfw3.h>

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{

	bool Input::IsKeyPressed(KeyCode key)
	{
		auto window = Application::Get().GetWindow().GetNativeWindow();
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		auto window = Application::Get().GetWindow().GetNativeWindow();
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		auto window = Application::Get().GetWindow().GetNativeWindow();
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