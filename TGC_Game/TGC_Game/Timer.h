#pragma once
#include <chrono>

class Timer {
public:
    Timer();  //�R���X�g���N�^

    void Start();  //�X�^�[�g����
    void Reset();  //���Z�b�g����
    double GetElapsedSeconds() const;  //�o�ߕb���擾����
    bool IsTimeUp(double durationSeconds) const;  //�^�C���A�b�v����

private:
    std::chrono::steady_clock::time_point startTime;  //
};
