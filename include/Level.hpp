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
#include "GameData.hpp"
#include "SideMenu.hpp"

// Controls the turrets, enemies, map
class Level : public Mode
{
	public:
		Level(sf::RenderWindow& window, std::shared_ptr<GameData> gameData);
		virtual void update(sf::Time deltaTime) final;
		virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;
        virtual void handleInnerChange(Action action) final;
	
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

		void checkGameOver();
		void collectRewards();
		void updateEnemies(sf::Time deltaTime);
		void updateTurrets(sf::Time deltaTime);
		void updateProjectiles(sf::Time deltaTime);
		void updateTexts();

		void loadMap();

	private:
		ResourceHolder<sf::Texture, Textures::ID> textures_;

		sf::Text levelText_;
		sf::Text creditsText_;
		sf::Text gameOverText_;

		Map* map_; ///< Hold by unique pointer elsewhere.
		std::shared_ptr<GameData> gameData_;

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

        bool isMenuOpen_;

        std::unique_ptr<SideMenu> sideMenu_;
};

#endif
