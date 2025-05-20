#pragma once
#include <chrono>

class Timer {
public:
    Timer(int limitSeconds);  // §ŒÀŠÔi•bj‚ğw’è‚µ‚Ä‰Šú‰»
    void start();
    void reset();
    int getRemainingTime() const;
    bool isTimeUp() const;

private:
    int limitSeconds;
    std::chrono::steady_clock::time_point startTime;
};
