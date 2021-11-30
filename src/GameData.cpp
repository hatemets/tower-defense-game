#include "../include/GameData.hpp"
#include "../include/auxiliary/constants.hpp"

GameData::GameData()
    : level_(1),
      credits_(NewGameCredits),
      isGameOver_(false)
{
}