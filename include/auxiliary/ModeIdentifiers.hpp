#ifndef MODE_IDENTIFIERS_HPP
#define MODE_IDENTIFIERS_HPP

namespace Modes
{
	enum class Type
	{
		MainMenu,
		LevelMenu,
		Level,
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
