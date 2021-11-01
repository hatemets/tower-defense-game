#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Node.hpp"
#include "auxiliary/ButtonData.hpp"

class Button : public Node
{
	public:
		Button(ButtonData attributes);

	private:
		sf::RectangleShape button_;
};


#endif
