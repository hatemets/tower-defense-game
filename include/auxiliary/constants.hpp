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

// Turret properties
const float TurretTextureOffset = 90; // turret texture angle (90 degrees = turret barrel points down in the texture)

const int GunTurretPrice = 10;
const float GunTurretRotationSpeed = 90.f; // 90 degrees per second
const float GunTurretRateOfFire = 5.f; // 5 shots per second
const float GunTurretRadarRange = 5.f; // 5 tiles
const float GunTurretProjectileRange = 5.f; // 5 tiles

const int DoubleGunTurretPrice = 30;
const float DoubleGunTurretRotationSpeed = 90.f; 
const float DoubleGunTurretRateOfFire = 5.f; 
const float DoubleGunTurretRadarRange = 5.f; 
const float DoubleGunTurretProjectileRange = 5.f; 

// Projectile properties
const float BulletSpeed = 5.f;       // 5 tiles per second
const float BulletFlightRange = 5.f; // 5 tiles
const int BulletMaxDamage = 20;      // 20 hit points (hit points are integers)

#endif
