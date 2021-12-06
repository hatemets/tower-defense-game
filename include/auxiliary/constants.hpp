#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <array>

// ----------------------- GENERAL --------------------------
// ----------------------------------------------------------
const unsigned int FramesPerSecond = 200;

// NOTE: The window has a resolution of 4:3
const int WindowWidth = 800;
const int WindowHeight = WindowWidth / 4 * 3;

const int TileCols = 20;
const int TileRows = TileCols / 4 * 3;

const int TileSize = WindowWidth / TileCols;

// The space between buttons
const float ButtonMargin = 20.f;

// Total number of playable levels
const int TotalLevels = 6;

// ----------------------- STYLING ---------------------------
// -----------------------------------------------------------
// Primary theme color for buttons
const std::array<int, 3> SecondaryColor = {00, 00, 80};

// Secondary theme color for texts and the like
const std::array<int, 3> PrimaryColor = {180, 180, 180};

// Buttons
/* const float ButtonWidth = 1.f / 4.f * WindowWidth; */
/* const float ButtonHeight = 1.f / 6.f * WindowHeight; */

/* const float ButtonPaddingX = 0.3f * ButtonWidth; */
/* const float ButtonPaddingY = 0.15f * ButtonHeight; */

const float ButtonScalar = 1.05f;

// Credits
const int NewGameCredits = 300;
const int CreditsTextFontSize = 24;
const float CreditsTextPaddingX = 5.f;
const bool CheatModeEnabled = true;



// ------------------------- MATH ----------------------------
// -----------------------------------------------------------
const float Pi = 3.14159f;
const float RadiansToDegrees = 180.f / Pi;
const float DegreesToRadians = Pi / 180.f;


// ------------------------ GAMEPLAY -------------------------
// -----------------------------------------------------------
// Levels
const int LevelTextFontSize = 24;
const int MaxLevel = 5;
const std::array<int, MaxLevel> LevelLimits = {0, 500, 1000, 2000, 4000};
const std::array<float, MaxLevel> LevelMinSpawnIntervals = {5.f, 4.f, 3.f, 2.f, 1.f};
const std::array<float, MaxLevel> LevelMaxSpawnIntervals = {10.f, 8.f, 6.f, 4.f, 2.f};
const float LevelFirstSpawnTime = 5.f;

// Game Over
const int GameOverTextFontSize = 96;

// Explosion properties
const float ExplosionExpansionTime = 0.1f;
const float ExplosionCooldownTime = 1.f;

// Turret properties
const float TurretTextureOffset = 90; // turret texture angle (90 degrees = turret barrel points down in the texture)
const float TurretScaler = 2.f;


namespace Projectiles
{
	struct Bullet
	{
		static constexpr float speed = 20.f; // tiles per second
		static constexpr float range = 5.f;	 // tiles
		static constexpr int damage = 20;	 // hit points (hit points are integers)
		static constexpr float size = 0.05f; // bullet diameter (if 0, drawn as vertex)
	};

	struct Bomb
	{
		static constexpr float speed = 12.f;		  // tiles per second
		static constexpr float range = 3.f;			  // tiles
		static constexpr float explosionRadius = 1.f; // damages enemies within N tiles
		static constexpr int damage = 80;			  // hit points (hit points are integers)
		static constexpr float size = 0.2f;			  // bomb diameter is 0.2 tiles
	};

	struct Missile
	{
		static constexpr float speed = 8.f;			   // tiles per second
		static constexpr float range = 15.f;		   // tiles
		static constexpr float explosionRadius = 1.5f; // damages enemies within N tiles
		static constexpr int damage = 200;			   // hit points (hit points are integers)
		static constexpr float size = 0.2f;			   // hit diameter is 0.2 tiles
	};
}


const bool GameHasVertexProjectiles = (Projectiles::Bullet::size == 0.f);


// Enemy specs
namespace Enemies
{
	const float HealthBarMargin = 0.8f;

	struct Orc
	{
		static constexpr int hitPoints = 800;
		static constexpr int reward = 10;
		static constexpr float speed = 2.5f;
		static constexpr float size = 0.6f;
	};

	struct Goblin
	{
		static constexpr int hitPoints = 500;
		static constexpr int reward = 20;
		static constexpr float speed = 3.5f;
		static constexpr float size = 0.5f; // Goblin diameter is 0.5 tiles
	};

	struct Troll
	{
		static constexpr int hitPoints = 1500;
		static constexpr int reward = 30;
		static constexpr float speed = 1.5f;
		static constexpr float size = 0.7f;
	};

	struct Slime
	{
		static constexpr int hitPoints = 2000;
		static constexpr int reward = 50;
		static constexpr float speed = 1.0f;
		static constexpr float size = 0.6f;
		static constexpr int babies = 5; // number of baby slimes created when dying
	};

	struct BabySlime
	{
		static constexpr int hitPoints = 100;
		static constexpr int reward = 10;
		static constexpr float speed = 1.0f;
		static constexpr float size = 0.3f;
	};

	struct Kobold
	{
		static constexpr int hitPoints = 250;
		static constexpr int reward = 40;
		static constexpr float speed = 4.0f;
		static constexpr float size = 0.4f;
	};
}


// Turret specs
namespace Turrets
{
	const float rotationSpeed = 270.f; // Degrees per second

	struct Gun
	{
		static constexpr int price = 100;
		static constexpr float firerate = 5.f; // Shots per second
		static constexpr float radarRange = 5.f;
	};

	struct DoubleGun
	{
		static constexpr int price = 300;
		static constexpr float firerate = 5.f;
		static constexpr float radarRange = 5.f;
	};

	struct TripleGun
	{
		static constexpr int price = 800;
		static constexpr float firerate = 5.f;
		static constexpr float radarRange = 5.f;
	};

	struct Bomb
	{
		static constexpr int price = 500;
		static constexpr float firerate = 2.f;
		static constexpr float radarRange = 5.f;
	};

	struct Missile
	{
		static constexpr int price = 1000;
		static constexpr float firerate = 0.3f;
		static constexpr float radarRange = 12.f;
	};
}

#endif
