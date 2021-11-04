#ifndef MODE_HPP
#define MODE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Node.hpp"

// Mode is an abstract class used for representing one "scene" currently
// displayed on the game window
// Each Mode object must have an enum of layers
class Mode : public Node
{
	public:
		Mode(sf::RenderWindow& window);
		virtual void update(sf::Time deltaTime) = 0;

	private:
		virtual void loadTextures() = 0;
		virtual void createScene() = 0;

	protected:
		// Reference to the original window
		sf::RenderWindow& window_;

		// Used for accessing the layer nodes
		std::vector<Node*> layers_;

		// The root node that all the other nodes stem from
		Node nodeTree_;
};

#endif

