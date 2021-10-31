#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include "ResourceHolder.hpp"
#include "auxiliary/ResourceIdentifiers.hpp"

class MainMenu
{
	public:
		MainMenu(sf::RenderWindow& window);
		void update(sf::Time deltaTime);
		void draw();

	private:
		sf::RenderWindow& window_;
};


#endif
