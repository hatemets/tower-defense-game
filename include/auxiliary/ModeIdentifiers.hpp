#ifndef MODE_IDENTIFIERS_HPP
#define MODE_IDENTIFIERS_HPP

namespace Modes
{
    enum class Action
    {
        // Changes the whole state
        ModeChange,

        // Doesn't do anything
        Idle,

        // Changes part of the state, but not the whole state
        SideMenuToggle
    };

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
		TotalTypes
	};

	/* Struct for passing information from Modes to World */
	struct ModeState
	{
		ModeState(Type type) : action(Action::ModeChange), type(type) {}
		ModeState(Action action) : action(action), type() {}
		
		ModeState() : action(Action::Idle), type() {}

		Action action;
		Type type;
	};

}

#endif
