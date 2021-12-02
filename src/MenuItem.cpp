#include "../include/MenuItem.hpp"
#include "../include/auxiliary/constants.hpp"
#include "../include/SideMenu.hpp"

// if queue number is n then it this item is nth counting the top
MenuItem::MenuItem(int price, Textures::ID turretID, Textures::ID baseID, TextureHolder& textureHolder, FontHolder& fonts_, sf::IntRect itemBounds, int queueNumber)
    : price_(price),
    text_(),
    turretSprite_(textureHolder.get(turretID)),
    turretBaseSprite_(textureHolder.get(baseID))
{
    text_.setFont(fonts_.get(Fonts::ID::SourceCodePro));
    text_.setString("$500");
    text_.setPosition(itemBounds.left, itemBounds.top);

    int verticalPadding = (int)(0.05 * itemBounds.height);
    int horizontalPadding = (int)(0.1 * itemBounds.width);

    sf::Vector2i position(itemBounds.left, itemBounds.top);

    auto imageBounds = turretBaseSprite_.getGlobalBounds();

    turretBaseSprite_.setOrigin(imageBounds.width / 2.f, imageBounds.height / 2.f);
    turretBaseSprite_.setScale(TurretScaler * TileSize / imageBounds.width, TurretScaler * TileSize / imageBounds.height);
    turretBaseSprite_.setPosition(itemBounds.left + horizontalPadding, itemBounds.top + horizontalPadding);

    imageBounds = turretSprite_.getGlobalBounds();

    turretSprite_.setOrigin(imageBounds.width / 2.f, imageBounds.height / 2.f);
    turretSprite_.setScale(TurretScaler * TileSize / imageBounds.width, TurretScaler * TileSize / imageBounds.height);

    turretSprite_.setPosition(itemBounds.left + horizontalPadding, itemBounds.top + horizontalPadding);
}

void MenuItem::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(turretBaseSprite_);
    target.draw(turretSprite_);
    target.draw(text_);
}
