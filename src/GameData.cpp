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
        std::ifstream ifs("./include/auxiliary/cache.txt");
        std::string credits{};
        std::getline(ifs, credits);
        credits_ = std::stoi(credits);
        std::cout << credits_ << std::endl;
    }
    // New game means there is no file
    catch (std::string& err)
    {
        credits_ = NewGameCredits;
    }
}


int GameData::getMaxOpenLevel()
{
    if (isNewGame)
    {
        return 0;
    }

	for (int level = MaxLevel; level > 0; level--)
	{
		if (LevelLimits[level - 1] <= credits_)
		{
			return level;
		}
	}
    return 0;
}
	
