#pragma once
#include <vector>

struct ScoreData {
    int correct;
    int sales;
};

class RankingManager {
public:
    static RankingManager& GetInstance();

    void WriteScore(int correct, int sales);
    std::vector<ScoreData> ReadScores();
    


private:
    RankingManager() = default;
};
