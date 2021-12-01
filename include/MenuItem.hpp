#ifndef MENUITEM_HPP
#define MENUITEM_HPP

#include "Node.hpp"
#include "ResourceHolder.hpp"
#include "auxiliary/constants.hpp"
#include "auxiliary/ResourceIdentifiers.hpp"
#include <SFML/Graphics.hpp>

// TODO: Fix recursive inclusion
#include "SideMenu.hpp"

using namespace Resources;
using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;
using FontHolder = ResourceHolder<sf::Font, Fonts::ID>;


class MenuItem : public Node
{
	public:
        MenuItem(int price, Textures::ID textureID, TextureHolder& textureHolder, FontHolder& fonts_, const SideMenu& sideMenu_);
            virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
        // Price of the turret
		const int price_;

        // The turret image
		sf::Sprite turretSprite_;

        // Text is the price in text form
        sf::Text text_;
};

#endif
