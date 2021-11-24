#ifndef SIDEMENU_HPP
#define SIDEMENU_HPP

#include "Node.hpp"
#include "MenuItem.hpp"
#include <array>

// TODO: Remove to constants
constexpr int totalTurrets = 5;

class SideMenu : public Node
{
	public:

	private:
		std::array<MenuItem, totalTurrets> menuItems_;
};

#endif
