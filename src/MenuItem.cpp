#include "../include/MenuItem.hpp"
#include "../include/auxiliary/constants.hpp"
#include "../include/SideMenu.hpp"

MenuItem::MenuItem(int price, Textures::ID textureID, TextureHolder& textureHolder, FontHolder& fonts_, const SideMenu& sideMenu_)
	: price_(price),
    text_(),
    turretSprite_(textureHolder.get(textureID))
{
    // TODO: Remove hardcoded values
    text_.setFont(fonts_.get(Fonts::ID::SourceCodePro)),

    auto menuBounds = sideMenu_.getGlobalBounds();

    // Prepare the resources
    turretSprite_.setPosition();
}

void MenuItem::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(turretSprite_);
    target.draw(text_);
}
