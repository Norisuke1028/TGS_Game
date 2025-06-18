#include "RankingManager.h"
#include <fstream>
#include <algorithm>

RankingManager& RankingManager::GetInstance() {
    static RankingManager instance;
    return instance;
}

void RankingManager::WriteScore(int correct, int sales) {
    int sum = correct * 50 + sales;

    LoadFromFile();  // 既存のデータを読み込み

    scores.push_back({ correct, sales, sum });

    // sumの値で降順にソート
    std::sort(scores.begin(), scores.end(), [](const ScoreData& a, const ScoreData& b) {
        return a.sum > b.sum;
        });

    // 上位3件までに制限
    if (scores.size() > 3) {
        scores.resize(3);
    }

    // 書き込み：correct sales sum の形式
    std::ofstream outFile("Resource/ScoreData/ranking.txt", std::ios::trunc);
    for (const auto& score : scores) {
        outFile << score.correct << " " << score.sales << " " << score.sum << std::endl;
    }
}


void RankingManager::LoadFromFile() {
    scores.clear();

    std::ifstream inFile("Resource/ScoreData/ranking.txt");
    int correct, sales, sum;

    while (inFile >> correct >> sales >> sum) {
        scores.push_back({ correct, sales, sum });
    }
}


const std::vector<ScoreData>& RankingManager::ReadScores() {
    LoadFromFile();  // 読み込んでおく
    return scores;
}
