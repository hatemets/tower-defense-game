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
			Level1Button,
			Level2Button,
			Level3Button,
			Level4Button,
			Level5Button,
			Level6Button,
			Level7Button,
			Level8Button,
			Level9Button,

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
			Kobold,

			// Health
			Health100,
			Health80,
			Health60,
			Health40,
			Health20,

			// Turrets
			GunTurret,
			DoubleGunTurret,
			TripleGunTurret,
			BombTurret,
			Missile,

			// Turret bases
			GunTurretBase,
			DoubleGunTurretBase,
			TripleGunTurretBase,
			BombTurretBase,
			MissileBase,
		};
	}

};

#endif
