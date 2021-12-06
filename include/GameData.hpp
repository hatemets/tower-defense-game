#ifndef GAME_DATA_HPP
#define GAME_DATA_HPP

class GameData
{
    public:
        GameData();

        int getMaxOpenLevel();

        int getLevel() const { return level_; }
        int getCredits() const { return credits_; }
        bool isGameOver() const { return isGameOver_; }

        void setLevel(int level) { level_ = level; }
        void addCredits(int credits) { isNewGame = false; credits_ += credits; }
        void removeCredits(int credits) { isNewGame = false; credits_ -= credits; }
        void setGameOver(bool val) { isGameOver_ = val; }

    private:
        int level_;
        int credits_;
        bool isGameOver_;
        bool isNewGame;
};

#endif
