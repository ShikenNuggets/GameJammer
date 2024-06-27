#ifndef JAMMER_TIMER_H
#define JAMMER_TIMER_H

#include <chrono>

namespace Jammer{
	class Timer{
	public:
		Timer();

		void Start();
		void Update();
		void Delay();

		float DeltaTime() const;

		static constexpr float MicroSecondsToSeconds(const std::chrono::microseconds& ms_){ return static_cast<float>(ms_.count()) / 1000000.0f; }

	private:
		float timeScale = 1.0f;

		std::chrono::microseconds startTime;
		std::chrono::microseconds previousTicks;
		std::chrono::microseconds currentTicks;

		std::chrono::microseconds GetSleepTime() const;
	};
}

#endif //!JAMMER_TIMER_H