#ifndef MODE_IDENTIFIERS_HPP
#define MODE_IDENTIFIERS_HPP

#include <string>
#include <iostream>

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

    enum class Action
    {
        ModeChange,
        ShowMessage,
        Idle
    };

	/* Struct for passing information from Modes to World */
	struct ModeState
	{
		explicit ModeState(Type type) : action(Action::ModeChange), type(type) {}
        explicit ModeState(Action action) : action(action), type() {}
		ModeState() : action(Action::Idle), type() {}

        Action action;
		Type type;
	};

}

#endif
