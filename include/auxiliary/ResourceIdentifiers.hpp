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
			LevelMenuBackground,

			// Enemies
			Goblin,

			// Turrets
			ArrowShooter,
			GunTurret,
			DoubleGunTurret,

			// Turret bases
			OrangeBase,
			DoubleGunTurretBase,
		};
	}

};

#endif
