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
const float TurretScaler = 2.f;


namespace Projectiles
{
	struct Bullet
	{
		static constexpr float speed = 20.f;   // tiles per second
		static constexpr float range = 5.f;	// tiles
		static constexpr int damage = 20;      // hit points (hit points are integers)
	};

	struct Bomb
	{
		static constexpr float speed = 12.f;			// tiles per second
		static constexpr float range = 3.f;			// tiles
		static constexpr float explosionRadius = 1.f;  // damages enemies within N tiles
		static constexpr int damage = 80;				// hit points (hit points are integers)
		static constexpr float size = 0.1f;
	};
}


// Enemy specs
namespace Enemies
{
	struct Goblin
	{
		static constexpr float goblinSpeed = 3.5f;
		static constexpr int hitPoints = 500;
		static constexpr float size = 0.5f; // Diameter 0.5 tiles
	};
}


// Turret specs
namespace Turrets
{
	const float rotationSpeed = 270.f; // Degrees per second

	struct Gun
	{
		static constexpr int price = 100;
		static constexpr int firerate = 5.f; // Shots per second
		static constexpr int radarRange = 5.f;
	};

	struct DoubleGun
	{
		static constexpr int price = 300;
		static constexpr int firerate = 5.f;
		static constexpr int radarRange = 5.f;
	};

	struct TripleGun
	{
		static constexpr int price = 800;
		static constexpr int firerate = 5.f;
		static constexpr int radarRange = 5.f;
	};

	struct Bomb
	{
		static constexpr int price = 500;
		static constexpr int firerate = 2.f;
		static constexpr int radarRange = 5.f;
	};
}


#endif
