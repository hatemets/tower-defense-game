#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include "ResourceHolder.hpp"
#include "auxiliary/ResourceIdentifiers.hpp"

// Controls the turrets, enemies, map
class Level
{
	public:
		explicit Level(sf::RenderWindow& window);
		void update(sf::Time deltaTime);
		void draw();
	
	private:
		enum class Layers
		{
			Background,
			Entities,
			HUD,
			// total count to get the number of members in the enum
			totalCount	 
		};

	private:
		void loadTextures();
		void createScene();

	private:
		sf::RenderWindow& window_;
		Node sceneTree_;
		ResourceHolder<sf::Texture, Textures::ID> textures_;

};

#endif
