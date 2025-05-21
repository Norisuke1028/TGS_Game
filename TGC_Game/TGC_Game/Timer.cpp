#include "Timer.h"

//�R���X�g���N�^
Timer::Timer() {
    Start();
}
//�X�^�[�g����
void Timer::Start() {
    startTime = std::chrono::steady_clock::now();
}
//���Z�b�g����
void Timer::Reset() {
    Start();
}
//�o�ߕb���擾����
double Timer::GetElapsedSeconds() const {
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = now - startTime;
    return elapsed.count();
}
//�^�C���A�b�v����
bool Timer::IsTimeUp(double durationSeconds) const {
    return GetElapsedSeconds() >= durationSeconds;
}
