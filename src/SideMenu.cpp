#include "../include/SideMenu.hpp"
#include "../include/auxiliary/constants.hpp"

const int menuWidth = WindowWidth / 5;
auto menuBounds = sf::IntRect(menuWidth, 0, menuWidth, WindowHeight);

SideMenu::SideMenu(TextureHolder& textures_, FontHolder& fonts_)
    : menuItems_(),
    background_(nullptr)
{
    sf::Texture& backgroundTexture = textures_.get(Textures::ID::SideMenuBackground);
    backgroundTexture.setRepeated(true);

    background_ = std::make_unique<BackgroundSprite>(backgroundTexture, menuBounds);
    background_->setPosition(menuBounds.left, menuBounds.top);

    for (int i = 0; i < TotalTurrets; ++i)
    {
        // TODO: Add the turrets with switch

        auto item = std::make_unique<MenuItem>(300, Textures::ID::GunTurret, Textures::ID::GunTurretBase, textures_, fonts_, menuBounds, i + 1);
        menuItems_.push_back(std::move(item));
    }
}


void SideMenu::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
    background_->drawSelf(target, states);  

    for (auto& item : menuItems_)
    {
        item->drawSelf(target, states);
    }
}
    
