#include "GameDataManager.h"

// �ÓI�C���X�^���X�̒�`�i�V���O���g���p�j
GameDataManager& GameDataManager::GetInstance() {
    static GameDataManager instance;
    return instance;
}

// �Z�b�^�[�E�Q�b�^�[�̎���
void GameDataManager::SetCorrect(int value) {
    correct = value;
}

int GameDataManager::GetCorrect() const {
    return correct;
}

void GameDataManager::SetSales(int value) {
    sales = value;
}

int GameDataManager::GetSales() const {
    return sales;
}
