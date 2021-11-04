#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include "ResourceHolder.hpp"
#include "auxiliary/ResourceIdentifiers.hpp"
#include "Mode.hpp"

// Controls the turrets, enemies, map
class MainMenu : public Mode
{
	public:
		MainMenu(sf::RenderWindow& window);
		virtual void update(sf::Time deltaTime) final;
		virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const;
	
	private:
		enum class Layers
		{
			Background,
			/* Buttons, */
			// total count to get the number of members in the enum
			totalCount	 
		};

	private:
		virtual void loadTextures() final;
		virtual void createScene() final;

	private:
		ResourceHolder<sf::Texture, Textures::ID> textures_;
};

#endif
