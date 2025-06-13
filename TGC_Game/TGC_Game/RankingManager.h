#pragma once
#include <vector>

struct ScoreData {
    int correct;
    int sales;
};

class RankingManager {
public:
    static RankingManager& GetInstance();

    void WriteScore(int correct, int sales);             // �ۑ�
    const std::vector<ScoreData>& ReadScores();          // �ǂݍ��݌��ʎ擾

private:
    RankingManager() = default;

    std::vector<ScoreData> scores;                       // �ǂݍ��񂾃����L���O

    void LoadFromFile();                                 // �����ŌĂяo���ǂݍ��ݏ���
};
