#include "../include/SideMenu.hpp"
#include "../include/auxiliary/constants.hpp"


SideMenu::SideMenu(TextureHolder& textures_)
    : background_(textures_.get(Textures::ID::SideMenuBackground))
{

    int menuWidth = WindowWidth / 5;

    // The menu is located in the right-hand side of the screen
    sf::IntRect menuBounds(WindowWidth - menuWidth, 0, menuWidth, WindowHeight);

}
