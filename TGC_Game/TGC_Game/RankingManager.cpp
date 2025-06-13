#include "RankingManager.h"
#include <fstream>
#include <algorithm>

RankingManager& RankingManager::GetInstance() {
    static RankingManager instance;
    return instance;
}

void RankingManager::WriteScore(int correct, int sales) {
    LoadFromFile();  // �܂������f�[�^�ǂݍ���

    scores.emplace_back(ScoreData{ correct, sales });

    // ���v�l�ō~���Ƀ\�[�g
    std::sort(scores.begin(), scores.end(), [](const ScoreData& a, const ScoreData& b) {
        return (a.correct + a.sales) > (b.correct + b.sales);
        });

    // �ő�3���܂�
    if (scores.size() > 3) {
        scores.resize(3);
    }

    // �t�@�C���ɏ�������
    std::ofstream outFile("Resource/ScoreData/ranking.txt", std::ios::trunc);
    for (const auto& score : scores) {
        outFile << score.correct << " " << score.sales << "\n";
    }
    outFile.close();
}

void RankingManager::LoadFromFile() {
    scores.clear();

    std::ifstream inFile("Resource/ScoreData/ranking.txt");
    int correct, sales;

    while (inFile >> correct >> sales) {
        scores.emplace_back(ScoreData{ correct, sales });
    }

    inFile.close();
}

const std::vector<ScoreData>& RankingManager::ReadScores() {
    LoadFromFile();  // �ǂݍ���ł���
    return scores;
}
