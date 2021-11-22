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

// Projectile properties
const float BulletSpeed = 20.f;       // tiles per second
const float BulletFlightRange = 5.f; // tiles
const int BulletMaxDamage = 20;      // hit points (hit points are integers)


// Enemy specs
namespace Enemies
{
	struct Goblin
	{
		static constexpr float goblinSpeed = 3.f;
		static constexpr int hitPoints = 500;
	};
}


// Turret specs
namespace Turrets
{
	const float rotationSpeed = 180.f; // Degrees per second

	struct Gun
	{
		static constexpr int price = 100;
		static constexpr int firerate = 5.f; // Shots per second
		static constexpr int radarRange = 5.f;
		static constexpr int projectileRange = 5.f;
	};

	struct DoubleGun
	{
		static constexpr int price = 300;
		static constexpr int firerate = 5.f;
		static constexpr int radarRange = 5.f;
		static constexpr int projectileRange = 5.f;
	};
}


#endif
