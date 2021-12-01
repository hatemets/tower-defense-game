#ifndef SIDEMENU_HPP
#define SIDEMENU_HPP

#include "Node.hpp"
#include "MenuItem.hpp"
#include "auxiliary/ResourceIdentifiers.hpp"
#include <array>

// TODO: Remove to constants
constexpr int totalTurrets = 5;

using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;

class SideMenu : public Node
{
	public:
        SideMenu(TextureHolder& textures_);

	private:
        // The rectangle shaped background of the sidemenu
        sf::Texture background_;

        // The list of items that are open for purchase
		std::array<MenuItem, totalTurrets> menuItems_;
};

#endif
