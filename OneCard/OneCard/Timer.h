#pragma once
#include <chrono>
#include "IPrint.h"
using namespace std::chrono;


class Timer : public IPrint {
private:
	system_clock::time_point start;
	bool active;
	const unsigned int setting_timer;

public:
	Timer(unsigned int t);
	void ResetTimer();
	int GetTimerBySec() const;
	void SetInactive();
	bool IsTimerOver();
	void Print(int x, int y) const;
};



Timer::Timer(unsigned int t) : start(system_clock::now()), active(false), setting_timer(t) {

}

void Timer::ResetTimer() {
	start = system_clock::now();
	active = true;
}

int Timer::GetTimerBySec() const{
	if (active) {
		system_clock::time_point current = system_clock::now();
		seconds sec = duration_cast<seconds>(current - start);
		int timer_value = setting_timer - sec.count();

		return timer_value;
	}
	else return 0;
}

void Timer::SetInactive() {
	active = false;
}

bool Timer::IsTimerOver(){
	if (GetTimerBySec() <= 0)
		active = false;
	return !active;
}

void Timer::Print(int x, int y) const {
	ConsoleConfig::XYPrint(x, y, "________");
	ConsoleConfig::XYPrint(x, y + 1, "|      |");
	ConsoleConfig::XYPrint(x, y + 2, "| TIME |");
	int sec = GetTimerBySec();
	std::string temp = std::to_string(sec);
	if (sec < 10)
		temp = "0" + temp;
	ConsoleConfig::XYPrint(x, y + 3, "|  " + temp + "  |");
	ConsoleConfig::XYPrint(x, y + 4, "|______|");
}