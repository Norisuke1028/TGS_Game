#pragma once

class GameDataManager {
private:
    int correct = 0;
    int sales = 0;

    // �R���X�g���N�^��private�ɂ��ĊO������new�ł��Ȃ��悤�ɂ���
    GameDataManager() {}

public:
    // �V���O���g���̃C���X�^���X�擾
    static GameDataManager& GetInstance();

    // �Z�b�^�[
    void SetCorrect(int value);
    void SetSales(int value);

    // �Q�b�^�[
    int GetCorrect() const;
    int GetSales() const;

    // �R�s�[�֎~�i�V���O���g���Ȃ̂Łj
    GameDataManager(const GameDataManager&) = delete;
    GameDataManager& operator=(const GameDataManager&) = delete;
};
