#include "Timer.h"

Timer::Timer(int limitSeconds) : limitSeconds(limitSeconds) {}

void Timer::start() {
    startTime = std::chrono::steady_clock::now();
}

void Timer::reset() {
    start();
}

int Timer::getRemainingTime() const {
    auto now = std::chrono::steady_clock::now();
    int elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
    return limitSeconds - elapsed;
}

bool Timer::isTimeUp() const {
    return getRemainingTime() <= 0;
}
