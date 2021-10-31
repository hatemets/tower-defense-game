#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>
#include "Node.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

class World
{
	public:
		explicit World(sf::RenderWindow& window);
		void operate(sf::Time deltaTime);

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
};

#endif
