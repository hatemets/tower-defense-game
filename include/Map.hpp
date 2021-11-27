#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include "auxiliary/ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"

using namespace Resources;

class Map : public Node
{
    public:
        Map(const std::string& filename, ResourceHolder<sf::Texture, Textures::ID>& textures);

    private:
        virtual void drawSelf(sf::RenderTarget &target, sf::RenderStates states) const;

    public:
		static float calculateDistance(const sf::Vector2f posA, const sf::Vector2f posB);
		static float calculateAngle(const sf::Vector2f posA, const sf::Vector2f posB);
		static bool isContact(const sf::Vector2f posA, float aRadius, const sf::Vector2f posB, float bRadius);

    public:
        // returns random path from a random spawn to a random base
        std::pair<std::vector<std::pair<int, int>>::const_iterator, std::vector<std::pair<int, int>>::const_iterator> getRandomPath() const;
        // returns the shortest path from a random spawn to the nearest base
        std::pair<std::vector<std::pair<int, int>>::const_iterator, std::vector<std::pair<int, int>>::const_iterator> getShortestPath() const;
        const std::vector<std::pair<int, int>>& getTurretBaseTiles() const;
        bool static isMember(int row, int col, const std::vector<std::pair<int, int>>& container);

    private:
        void loadFile(const std::string &fileName);
        void loadTextures();

        void findPaths();
        void findPaths(std::vector<std::pair<int, int>>& path);

		bool isSpawn(int row, int col) const { return isMember(row, col, spawnTiles_); }
		bool isRoad(int row, int col) const { return isMember(row, col, roadTiles_); }
		bool isBase(int row, int col) const { return isMember(row, col, baseTiles_); }
		bool isTurretBase(int row, int col) const { return isMember(row, col, turretBaseTiles_); }

		void loadTileset(const std::vector<std::pair<int, int>>& tiles_, Textures::ID style = Textures::ID::DirtPath, float scale = 1.f);

    private:
		ResourceHolder<sf::Texture, Textures::ID>& textures_;

        // Tiles are listed as row,col pairs
        std::vector<std::pair<int, int>> spawnTiles_;
        std::vector<std::pair<int, int>> roadTiles_;
        std::vector<std::pair<int, int>> baseTiles_;
        std::vector<std::pair<int, int>> turretBaseTiles_;
        std::vector<std::vector<std::pair<int, int>>> paths_;
        std::vector<int> shortestPathIndexes_;
        std::vector<std::shared_ptr<sf::Sprite>> mapPictures_; 
};

#endif
