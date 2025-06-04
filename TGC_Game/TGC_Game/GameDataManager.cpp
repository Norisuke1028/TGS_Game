#include "GameDataManager.h"

// 静的インスタンスの定義（シングルトン用）
GameDataManager& GameDataManager::GetInstance() {
    static GameDataManager instance;
    return instance;
}

// セッター・ゲッターの実装
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
