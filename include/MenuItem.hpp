#ifndef MENUITEM_HPP
#define MENUITEM_HPP

#include "Node.hpp"
#include "ResourceHolder.hpp"
#include "auxiliary/constants.hpp"
#include "auxiliary/ResourceIdentifiers.hpp"
#include <SFML/Graphics.hpp>

using namespace Resources;
using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;

class MenuItem : public Node
{
	public:
		MenuItem(int price, Textures::ID textureID, TextureHolder& textureHolder);

	private:
		const int price_;
		sf::Sprite turretSprite_;

};

#endif
