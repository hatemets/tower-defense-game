#ifndef RESOURCE_IDENTIFIERS_HPP
#define RESOURCE_IDENTIFIERS_HPP

namespace Resources
{
	enum class ID
	{
		// Icons

		// Patterns for map
		// Area is for turrets
		// Path is for enemies
		GrassArea,
		SandPath,

		// Enemies
		Goblin,

		// Turrets
		ArrowShooter,

		// Button names
		StartButton,

		// NOTE: This button leads the user to main menu
		// It does NOT belong to main menu itself
		HomeButton,
		QuitButton,
		PauseButton,

		// Fonts
		SourceCodePro
	};
};

#endif
