#include "RankingManager.h"
#include <fstream>
#include <algorithm>

RankingManager& RankingManager::GetInstance() {
    static RankingManager instance;
    return instance;
}

void RankingManager::WriteScore(int correct, int sales) {
    int sum = correct * 50 + sales;

    LoadFromFile();  // �����̃f�[�^��ǂݍ���

    scores.push_back({ correct, sales, sum });

    // sum�̒l�ō~���Ƀ\�[�g
    std::sort(scores.begin(), scores.end(), [](const ScoreData& a, const ScoreData& b) {
        return a.sum > b.sum;
        });

    // ���3���܂łɐ���
    if (scores.size() > 3) {
        scores.resize(3);
    }

    // �������݁Fcorrect sales sum �̌`��
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
    LoadFromFile();  // �ǂݍ���ł���
    return scores;
}
