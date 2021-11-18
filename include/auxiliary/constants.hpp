#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <array>

// General
const unsigned int FramesPerSecond = 200;

// NOTE: The window MUST have a resolution of 4:3
// TODO: Write a guard for ensuring the aspect ratio
const int WindowWidth = 800;
const int WindowHeight = 600;

const int TileCols = 20;
const int TileRows = 15;

const int TileSize = WindowWidth / TileCols;

// Primary theme color for buttons
const std::array<int, 3> PrimaryColor = {00, 00, 80};

// Secondary theme color for texts and the like
const std::array<int, 3> SecondaryColor = {180, 180, 180};

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
