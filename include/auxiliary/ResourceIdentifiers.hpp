#ifndef RESOURCE_IDENTIFIERS_HPP
#define RESOURCE_IDENTIFIERS_HPP

namespace Resources
{
	namespace Buttons
	{
		enum class ID
		{
			// To level menu
			Start,
			CheatMode,
			Level1,
			Level2,
			Level3,
			Level4,
			Level5,
			Level6,
			Level7,
			Level8,
			Level9,

			// Buy menu
			BuyGunTurret,
			BuyDoubleGunTurret,
			BuyTripleGunTurret,
			BuyBombTurret,
			BuyMissileTurret,
			CloseBuyMenu,

			// Sell menu
			SellTurret,
			CloseSellMenu,

			// To main menu
			Home,
			Quit,
			Pause,
            CloseMessage,
			LevelMenu,
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
