#pragma once
#include <chrono>

class Timer {
public:
    Timer(int limitSeconds);  // �������ԁi�b�j���w�肵�ď�����
    void start();
    void reset();
    int getRemainingTime() const;
    bool isTimeUp() const;

private:
    int limitSeconds;
    std::chrono::steady_clock::time_point startTime;
};
