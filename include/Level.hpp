#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include "Map.hpp"
// #include "ResourceHolder.hpp"
#include "auxiliary/ResourceIdentifiers.hpp"
#include "Mode.hpp"
#include "Enemy.hpp"
#include "Turret.hpp"

// Controls the turrets, enemies, map
class Level : public Mode
{
	public:
		Level(sf::RenderWindow& window);
		virtual void update(sf::Time deltaTime) final;
	
	private:
		enum class Layers
		{
			Background,
			Entities,
			SideMenu,
			HUD,
			// total count of enum values
			TotalCount	 
		};

	private:
		virtual void loadResources() final;
		virtual void createScene() final;

	private:
		ResourceHolder<sf::Texture, Textures::ID> textures_;

		Map* map_; ///< Hold by unique pointer elsewhere.
		Enemies* enemies_; ///< Hold by unique pointer elsewhere.
		Turrets* turrets_; ///< Hold by unique pointer elsewhere.
};

#endif
