#ifndef STATE_CHANGE_HPP
#define STATE_CHANGE_HPP

#include "auxiliary/ModeIdentifiers.hpp"

struct ModeChange
{
	ModeChange(Modes::Type mode) : mode(mode) {}

	Modes::Type mode;
};

#endif
