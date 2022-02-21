#pragma once

namespace Eye {

	class Timestep
	{
	public:
		Timestep(float time_s = 0.f)
			: m_Time(time_s)
		{
		}

		operator float() const { return GetSeconds(); }

		inline float GetSeconds() const { return m_Time; }
		inline float GetMilliseconds() const { return 1000.f * m_Time; }

	private:
		float m_Time;
	};

}