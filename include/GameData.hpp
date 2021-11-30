#ifndef GAME_DATA_HPP
#define GAME_DATA_HPP

class GameData
{
    public:
        GameData();

        int getLevel() const { return level_; }
        int getCredits() const { return credits_; }
        bool isGameOver() const { return isGameOver_; }

        void setLevel(int level) { level_ = level; }
        void addCredits(int credits) { credits_ += credits; }
        void setGameOver() { isGameOver_ = true; }

    private:
        int level_;
        int credits_;
        bool isGameOver_;
};

#endif
