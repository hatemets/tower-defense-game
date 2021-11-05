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
	
	private:
		enum class Layers
		{
			Background,
			Buttons,
			// total count of enum values
			totalCount	 
		};

	private:
		virtual void loadResources() final;
		virtual void createScene() final;

	private:
		ResourceHolder<sf::Texture, Resources::ID> textures_;
};

#endif
