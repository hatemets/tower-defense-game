#ifndef MODE_IDENTIFIERS_HPP
#define MODE_IDENTIFIERS_HPP

namespace Modes
{
	enum class Type
	{
		MainMenu,
		LevelMenu,
		NewGame,
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
        Quit,
		TotalTypes
	};

	/* Struct for passing information from Modes to World */
	struct ModeState
	{
		ModeState(Type type) : modeChange(true), type(type) {}
		ModeState() : modeChange(false), type() {}

		bool modeChange;
		Type type;
	};

}

#endif
