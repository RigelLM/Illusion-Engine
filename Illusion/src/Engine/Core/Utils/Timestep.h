/*
 * ===================== Timestep.h ===========================
 *                        -- ils --
 *                                         CREATE -- 2023.01.20
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The Timstep class
 * Calculate the time spend on rendering each frame
 * ----------------------------
 */
#pragma once

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	// The Timestep class
	class Timestep
	{
	public:
		Timestep(float time)
			:m_Time(time)
		{

		}

		// Override the float cast operator to simplify the operation
		operator float() { return m_Time; }

		// Get the time spent on rendering each frame in different units
		const float GetSeconds() const { return m_Time; }

		const float GetMilleSeconds() const { return m_Time * 1000.0f; }

	private:
		// Store the time spent on rendering a frame
		float m_Time;
	};


	//--------------------namespace: Illusion ends--------------------
}

