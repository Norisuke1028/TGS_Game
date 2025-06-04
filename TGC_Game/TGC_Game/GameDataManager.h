#pragma once

class GameDataManager {
private:
    int correct = 0;
    int sales = 0;

    // コンストラクタをprivateにして外部からnewできないようにする
    GameDataManager() {}

public:
    // シングルトンのインスタンス取得
    static GameDataManager& GetInstance();

    // セッター
    void SetCorrect(int value);
    void SetSales(int value);

    // ゲッター
    int GetCorrect() const;
    int GetSales() const;

    // コピー禁止（シングルトンなので）
    GameDataManager(const GameDataManager&) = delete;
    GameDataManager& operator=(const GameDataManager&) = delete;
};
