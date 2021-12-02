#ifndef SIDEMENU_HPP
#define SIDEMENU_HPP

#include "Node.hpp"
#include "MenuItem.hpp"
#include "auxiliary/ResourceIdentifiers.hpp"
#include "BackgroundSprite.hpp"
#include <vector>
#include <memory>

using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;
using FontHolder = ResourceHolder<sf::Font, Fonts::ID>;

class SideMenu : public Node
{
    public:
        SideMenu(TextureHolder& textures_, FontHolder& fonts_);
        virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        // The list of items that are open for purchase
        std::vector<std::unique_ptr<MenuItem>> menuItems_;

        // The rectangle shaped background of the sidemenu
        std::unique_ptr<BackgroundSprite> background_;
};

#endif
