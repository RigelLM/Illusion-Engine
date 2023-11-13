/*
 * ========================== Input.h ==========================
 *                             -- ils --
 *                                          CREATE -- 2023.01.12
 *                                          MODIFY --
 * -------------------------------------------------------------
 * The abstract Input class
 * Containing static methods that
 * can be called outside of the class
 *
 * Some KeyCodes and MouseButtonCodes
 * ----------------------------
 */

#pragma once

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