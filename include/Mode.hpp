#ifndef MODE_HPP
#define MODE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Node.hpp"
#include "ResourceHolder.hpp"
#include "Button.hpp"
#include "GameData.hpp"
#include "auxiliary/ModeIdentifiers.hpp"
#include "auxiliary/ResourceIdentifiers.hpp"

using namespace Modes;
using namespace Resources;

// Mode is an abstract class used for representing one "scene" currently
// displayed on the game window
// Each Mode object must have an enum of layers
class Mode : public Node
{
	public:
		Mode(sf::RenderWindow& window, std::shared_ptr<GameData> gameData);
		virtual ~Mode() = default;
    	Mode(const Mode&) = delete; // disallow copying
    	Mode& operator=(const Mode&) = delete; // disallow assign

		virtual ModeState handleInput(sf::Vector2i mousePos);
        /* ResourceHolder<sf::Font, Fonts::ID>& getFonts() { return fonts_; } */
        /* ButtonHolder<Buttons::ID>& getButtonShapes() { return buttonShapes_; } */

	private:
		virtual void loadResources() = 0;
		virtual void createScene() = 0;
		virtual void addButtons() = 0;
		virtual void addBackground() = 0;


	protected:
		void initializePointers(std::size_t layerCount);
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

		// Fonts
		ResourceHolder<sf::Font, Fonts::ID> fonts_;

		// A container storing button pointers
		std::vector<const Button*> buttons_;

		// Holds all the shapes (graphics) of buttons
		ButtonHolder<Buttons::ID> buttonShapes_;

        std::shared_ptr<GameData> gameData_;
};

#endif

