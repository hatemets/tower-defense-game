#include "../include/GameData.hpp"
#include "../include/auxiliary/constants.hpp"
#include <fstream>
#include <iostream>

GameData::GameData()
    : level_(1),
      isGameOver_(false),
      isNewGame(true)
{
}


int GameData::getMaxOpenLevel()
{
    try
    {
        isNewGame = false;
        std::ifstream ifs("./include/auxiliary/cache.txt");
        std::string lvl{};
        std::getline(ifs, lvl);

        // The value must be valid (the max value is TotalLevels)
        return std::stoi(lvl);
    }
    // New game means there is no file
    catch (std::string& err)
    {
        return 1;
    }
}
	

void GameData::setGameOver(bool val)
{ 
    isGameOver_ = val;
}
