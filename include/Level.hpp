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
		Level(sf::RenderWindow& window, sf::Time minSpawnInterval, sf::Time maxSpawnInterval);
		virtual void update(sf::Time deltaTime) final;
		virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const;
	
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

		void updateEnemies(sf::Time deltaTime);
		void updateTurrets(sf::Time deltaTime);

	private:
		ResourceHolder<sf::Texture, Textures::ID> textures_;

		Map* map_; ///< Hold by unique pointer elsewhere.

		// Enemies
		std::list<std::shared_ptr<Enemy>> enemies_;
		sf::Time minSpawnInterval_;
		sf::Time maxSpawnInterval_;
		sf::Time nextSpawn_;

		// Turrets
		std::list<std::shared_ptr<Turret>> turrets_;
};

#endif
