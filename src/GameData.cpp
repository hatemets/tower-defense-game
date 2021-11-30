#include "../include/GameData.hpp"
#include "../include/auxiliary/constants.hpp"

GameData::GameData()
    : level_(1),
      credits_(NewGameCredits),
      isGameOver_(false),
      isNewGame(true)
{
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
	