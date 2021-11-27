#ifndef RESOURCE_IDENTIFIERS_HPP
#define RESOURCE_IDENTIFIERS_HPP

namespace Resources
{
	namespace Buttons
	{
		enum class ID
		{
			// To level menu
			StartButton,

			// To main menu
			HomeButton,
			QuitButton,
			PauseButton,
			LevelMenuButton,
		};

	}

	namespace Fonts
	{
		enum class ID
		{
			SourceCodePro
		};
	}

	namespace Textures
	{
		enum class ID
		{
			// Icons

			// Patterns for map
			// Area is for turrets
			// Path is for enemies
			GrassArea,
			SandPath,
			DirtPath,
			Flag,
			LevelMenuBackground,

			// Enemies
			Goblin,
			Orc,
			Troll,
			Slime, // used also by BabySlime

			// Turrets
			GunTurret,
			DoubleGunTurret,
			TripleGunTurret,
			BombTurret,

			// Turret bases
			GunTurretBase,
			DoubleGunTurretBase,
			TripleGunTurretBase,
			BombTurretBase,
		};
	}

};

#endif
