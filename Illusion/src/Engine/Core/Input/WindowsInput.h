/*
 * ========================== WindowsInput.h ==========================
 *                              -- ils --
 *                                                 CREATE -- 2023.01.13
 *                                                 MODIFY --
 * -------------------------------------------------------------------
 * Input method implementation for windows
 * ----------------------------
 */


#pragma once

#include "Input.h"

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	class WindowsInput : public Input
	{
	protected:

		// Implementations for the virtual function for windows platform
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
	//--------------------namespace: Illusion ends--------------------
}