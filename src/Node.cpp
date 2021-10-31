#include "../include/Node.hpp"

Node::Node()
	: parent_{nullptr}, children_{}
{
}

// Moves the child to children list
void Node::addChild(std::unique_ptr<Node> child)
{
	child->parent_ = this;
	children_.push_back(std::move(child));
}

// Draws all the children (and their children)
void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const std::unique_ptr<Node>& child : children_)
	{
		child->draw(target, states);
	}
}
