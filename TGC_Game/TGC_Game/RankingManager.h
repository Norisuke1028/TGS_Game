#pragma once
#include <vector>

struct ScoreData {
    int correct;
    int sales;
    int sum;
};

class RankingManager {
public:
    static RankingManager& GetInstance();

    void WriteScore(int correct, int sales);             // 保存
    const std::vector<ScoreData>& ReadScores();          // 読み込み結果取得

private:
    RankingManager() = default;

    std::vector<ScoreData> scores;                       // 読み込んだランキング

    void LoadFromFile();                                 // 内部で呼び出す読み込み処理
};
