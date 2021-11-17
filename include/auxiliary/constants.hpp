#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// General
const unsigned int FramesPerSecond = 200;

// NOTE: The window MUST have a resolution of 4:3
// TODO: Write a guard for ensuring the aspect ratio
const int WindowWidth = 800;
const int WindowHeight = 600;

const int TileCols = 20;
const int TileRows = 15;

const int TileSize = WindowWidth / TileCols;

// Math
const float Pi = 3.14159f;
const float RadiansToDegrees = 180.f / Pi;
const float DegreesToRadians = Pi / 180.f;

// Buttons
const float ButtonWidth = 1.f / 4.f * WindowWidth;
const float ButtonHeight = 1.f / 6.f * WindowHeight;

const float ButtonPaddingX = 1.f / 4.f * ButtonWidth;
const float ButtonPaddingY = 1.f / 8.f * ButtonHeight;

#endif
