#include "pch.h"
#include "Timer.h"

#include <GLFW/glfw3.h>

namespace Illusion
{

	Timer::Timer(float stoptime)
		:m_StartTime(0.0f), m_CurrentTime(0.0f), m_StopTime(stoptime), m_RunningTime(0.0f)
	{

	}

	void Timer::SetTime(float stoptime)
	{
		m_StopTime = stoptime;
	}

	void Timer::Start()
	{
		m_IsStoped = false;
		m_StartTime = (float)glfwGetTime();
	}

	void Timer::Update()
	{
		if (!m_IsStoped)
		{
			m_CurrentTime = (float)glfwGetTime();
			m_RunningTime = m_CurrentTime - m_StartTime;
			if (m_RunningTime > m_StopTime)
			{
				m_IsStoped = true;
			}
		}
	}

	bool Timer::Check()
	{
		return m_IsStoped;
	}

	float Timer::GetTime()
	{
		return m_RunningTime;
	}
}
