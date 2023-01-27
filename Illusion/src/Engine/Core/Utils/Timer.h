#pragma once

namespace Illusion
{

	class Timer
	{
	public:

		Timer(float stoptime = 0.0f);
		~Timer() {};

		void SetTime(float time);

		void Start();

		void Update();

		bool Check();

		float GetTime();

	private:

		float m_StartTime;
		float m_CurrentTime;

		float m_StopTime;
		float m_RunningTime;

		float m_IsStoped = true;
	};

}
