#ifndef LAYER_IDENTIFIERS_HPP
#define LAYER_IDENTIFIERS_HPP

// NOTE: MainMenu only needs 2 layers (for background and buttons), so one of
// the enum values will not be used in that case
// Level needs all 3 layers (background, entities, HUD)
enum class Layers
{
	Background,
	Objects,
	Foreground,

	// total count to get the number of members in the enum
	totalCount
};

#endif
