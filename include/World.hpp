#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>
#include "Node.hpp"
// #include "ResourceHolder.hpp"
#include "auxiliary/ResourceIdentifiers.hpp"
#include "Level.hpp"

class World
{
	public:
		explicit World(sf::RenderWindow& window);
		void update(sf::Time deltaTime);
		void draw();

	public:
		enum class States
		{
			Menu,
			Pause,
			Level
		};
	
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
		sf::RenderWindow& window_;
		States currentState_;
		std::vector<std::shared_ptr<Level>> levels_;
		std::shared_ptr<Level> currentLevel_;
};

#endif
