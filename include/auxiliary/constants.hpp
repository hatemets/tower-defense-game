#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// General
const unsigned int FramesPerSecond = 200;
const int TileSize = 40;
const int TileRows = 20;
const int TileCols = 20;
const int WindowWidth = TileSize * TileCols;
const int WindowHeight = TileSize * TileRows;

// Math
const float Pi = 3.14159;
const float RadiansToDegrees = 180 / Pi;
const float DegreesToRadians = Pi / 180;

// Buttons
const float ButtonWidth = 1.f / 4.f * WindowWidth;
const float ButtonHeight = 1.f / 6.f * WindowHeight;

const float ButtonPaddingX = 1.f / 4.f * ButtonWidth;
const float ButtonPaddingY = 1.f / 8.f * ButtonHeight;

#endif
