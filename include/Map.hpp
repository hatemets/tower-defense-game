#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include "Turret.hpp"
#include "Projectile.hpp"
#include "Enemy.hpp"


class Map
{
	public:
		Map(sf::RenderWindow& window, const std::string& fileName);
		void draw();

    public:
        // these probably will be moved to level
        void update(sf::Time deltaTime);
	
    private:
        // these probably will be moved to level
        std::vector<std::shared_ptr<Turret>> turrets_;
        std::vector<std::shared_ptr<Projectile>> projectiles_;
        std::vector<std::shared_ptr<Enemy>> enemies_;

	private:
        void loadFile(const std::string& fileName);
		void loadTextures();

	private:
		sf::RenderWindow& window_;
		std::vector<std::pair<int, int>> roadTiles_;
		std::vector<std::pair<int, int>> turretBaseTiles_;
		std::vector<std::shared_ptr<sf::Shape>> mapPictures_; // Shapes probably should be replaced with Textures
};



#endif