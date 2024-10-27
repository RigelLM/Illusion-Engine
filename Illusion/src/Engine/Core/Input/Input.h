#pragma once

/*****************************************************************//**
 * \file   Input.h
 * \brief  The abstract input class, containing static 
 * methods that can be called outside of the class
 * 
 * \author Mian Li
 * \date   January 2023
 *********************************************************************/


#include "KeyCode.h"
#include "MouseCode.h"

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	class Input
	{

	public:

		// Static methods that could be used outside of this class
		// Call the virtual function that would be implemented in the inhirated class
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

	};
	//--------------------namespace: Illusion ends--------------------
}