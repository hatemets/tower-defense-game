#include "../include/GameData.hpp"
#include "../include/auxiliary/constants.hpp"
#include <fstream>
#include <iostream>

GameData::GameData()
    : level_(1),
      credits_(),
      isGameOver_(false),
      isNewGame(true)
{
    try
    {
        isNewGame = false;

        std::ifstream ifs("./include/auxiliary/cache.txt");
        std::string credits{};
        std::getline(ifs, credits);
        credits_ = std::stoi(credits);

        if (credits_ < NewGameCredits)
        {
            credits_ = NewGameCredits;
        }
    }
    // New game means there is no file
    catch (std::string& err)
    {
        isNewGame = true;
        credits_ = NewGameCredits;
    }
}


int GameData::getMaxOpenLevel()
{
    if (isNewGame)
    {
        return 1;
    }

	for (int level = TotalLevels; level > 0; level--)
	{
		if (LevelLimits[level - 1] <= credits_)
        {
            return level;
		}
	}

    return 1;
}
	

void GameData::setGameOver(bool val)
{ 
    isGameOver_ = val;
    if (!isGameOver_ && credits_ < NewGameCredits)
    {
        credits_ = NewGameCredits;
    }
}
