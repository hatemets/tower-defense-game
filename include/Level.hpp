#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include "ResourceHolder.hpp"
#include "auxiliary/ResourceIdentifiers.hpp"
#include "Mode.hpp"

// Controls the turrets, enemies, map
class Level : public Mode
{
	public:
		Level(sf::RenderWindow& window);
		virtual void update(sf::Time deltaTime) final;
		virtual void draw() final;
	
	private:
		enum class Layers
		{
			Background,
			Entities,
			SideMenu,
			HUD,
			// total count to get the number of members in the enum
			totalCount	 
		};

	private:
		virtual void loadTextures() final;
		virtual void createScene() final;

	private:
		ResourceHolder<sf::Texture, Textures::ID> textures_;
		// TODO:
		// Add turret contaienr
		// Add enemy container
		// Load a map from a textfile
};

#endif
