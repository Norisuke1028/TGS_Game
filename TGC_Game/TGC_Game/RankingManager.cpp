#include "RankingManager.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

RankingManager& RankingManager::GetInstance() {
    static RankingManager instance;
    return instance;
}

void RankingManager::WriteScore(int correct, int sales) {
    std::vector<ScoreData> scores = ReadScores(); // 既存のスコアを読み込み

    // 今回のスコアを追加
    scores.push_back({ correct, sales });

    // 合計値が高い順にソート
    std::sort(scores.begin(), scores.end(), [](const ScoreData& a, const ScoreData& b) {
        return (a.correct + a.sales) > (b.correct + b.sales);
        });

    // 最大3件まで保持
    if (scores.size() > 3) {
        scores.resize(3);
    }

    // 書き込み
    std::ofstream ofs("ranking.txt");
    for (const auto& score : scores) {
        ofs << score.correct << " " << score.sales << std::endl;
    }
}

std::vector<ScoreData> RankingManager::ReadScores() {
    std::vector<ScoreData> scores;
    std::ifstream ifs("ranking.txt");
    int correct, sales;

    while (ifs >> correct >> sales) {
        scores.push_back({ correct, sales });
    }

    return scores;
}


