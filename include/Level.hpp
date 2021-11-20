#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include "Map.hpp"
#include "auxiliary/ResourceIdentifiers.hpp"
#include "Mode.hpp"
#include "Enemy.hpp"
#include "Turret.hpp"
#include "Projectile.hpp"

// Controls the turrets, enemies, map
class Level : public Mode
{
	public:
		Level(sf::RenderWindow& window, sf::Time minSpawnInterval, sf::Time maxSpawnInterval);
		virtual void update(sf::Time deltaTime) final;
		virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;
	
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
		virtual void addButtons() override;
		virtual void addBackground() override;

		void updateEnemies(sf::Time deltaTime);
		void updateTurrets(sf::Time deltaTime);
		void updateProjectiles(sf::Time deltaTime);

		void loadMap();

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

		// Projectiles 
		std::list<std::shared_ptr<Projectile>> projectiles_;
		sf::VertexArray projectileVertices_; // combined picture of all projectiles that can be drawn as a vertex
};

#endif
