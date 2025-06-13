#pragma once
#include <vector>

struct ScoreData {
    int correct;
    int sales;
};

class RankingManager {
public:
    static RankingManager& GetInstance();

    void WriteScore(int correct, int sales);             // •Û‘¶
    const std::vector<ScoreData>& ReadScores();          // “Ç‚İ‚İŒ‹‰Êæ“¾

private:
    RankingManager() = default;

    std::vector<ScoreData> scores;                       // “Ç‚İ‚ñ‚¾ƒ‰ƒ“ƒLƒ“ƒO

    void LoadFromFile();                                 // “à•”‚ÅŒÄ‚Ño‚·“Ç‚İ‚İˆ—
};
