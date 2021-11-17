#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include "Node.hpp"
// #include "Turret.hpp"
// #include "Projectile.hpp"
// #include "Enemy.hpp"

class Map : public Node
{
    public:
        Map(const std::string& fileName);

    private:
        virtual void drawSelf(sf::RenderTarget &target, sf::RenderStates states) const;

    public:
		static float calculateDistance(const sf::Vector2f posA, const sf::Vector2f posB);
		static float calculateAngle(const sf::Vector2f posA, const sf::Vector2f posB);
		static bool isContact(const sf::Vector2f posA, float aRadius, const sf::Vector2f posB, float bRadius);

    public:
        std::pair<std::vector<std::pair<int, int>>::const_iterator, std::vector<std::pair<int, int>>::const_iterator> getPath() const;
        const std::vector<std::pair<int, int>>& getTurretBaseTiles() const;
        bool static isMember(int row, int col, const std::vector<std::pair<int, int>>& container);

    private:
        void loadFile(const std::string &fileName);
        void loadTextures();
        bool isSpawn(int row, int col) const;
        bool isRoad(int row, int col) const;
        bool isBase(int row, int col) const;
        bool isTurretBase(int row, int col) const;
        void findPaths();

    private:
        // Tiles are listed as row,col pairs
        std::vector<std::pair<int, int>> spawnTiles_;
        std::vector<std::pair<int, int>> roadTiles_;
        std::vector<std::pair<int, int>> baseTiles_;
        std::vector<std::pair<int, int>> turretBaseTiles_;
        std::vector<std::vector<std::pair<int, int>>> paths_;
        std::vector<std::shared_ptr<sf::Shape>> mapPictures_; // Shapes probably should be replaced with Textures or Sprites
};

#endif
