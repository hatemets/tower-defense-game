#ifndef MODE_HPP
#define MODE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Node.hpp"
#include "auxiliary/ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"

// Mode is an abstract class used for representing one "scene" currently
// displayed on the game window
// Each Mode object must have an enum of layers
class Mode : public Node
{
	public:
		Mode(sf::RenderWindow& window);
		virtual ~Mode() = default;

	private:
		virtual void loadResources() = 0;
		virtual void createScene() = 0;
		virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		// Reference to the original window
		sf::RenderWindow& window_;

		// Used for accessing the layer nodes
		std::vector<Node*> layers_;

		// The root node that all the other nodes stem from
		Node nodeTree_;

		// Window dimensions
		sf::FloatRect windowBounds_;

		ResourceHolder<sf::Font, Resources::ID> fonts_;
};

#endif

