#ifndef GAME_DATA_HPP
#define GAME_DATA_HPP

class GameData
{
    public:
        GameData();

        int getMaxOpenLevel();

        int getLevel() const { return level_; }
        bool isGameOver() const { return isGameOver_; }

        void setLevel(int level) { level_ = level; }
        void setGameOver(bool val);

    private:
        int level_;
        bool isGameOver_;
        bool isNewGame;
};

#endif
