#include "../include/SideMenu.hpp"
#include "../include/auxiliary/constants.hpp"


SideMenu::SideMenu(TextureHolder& textures_, FontHolder& fonts_)
    : menuItems_(),
    background_(nullptr)
{
    const int menuWidth = (int)(WindowWidth * 0.28);
    auto menuBounds = sf::IntRect(WindowWidth - menuWidth, 0, menuWidth, WindowHeight);

    sf::Texture& backgroundTexture = textures_.get(Textures::ID::SideMenuBackground);
    backgroundTexture.setRepeated(true);

    background_ = std::make_unique<sf::Sprite>(backgroundTexture);
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
    target.draw(*background_.get(), states);

    for (auto& item : menuItems_)
    {
        item->drawSelf(target, states);
    }
}
    
