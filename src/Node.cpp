#include "../include/Node.hpp"

Node::Node()
	: parent_(nullptr),
	children_()
{
}


// Adds the child to children vector
void Node::addChild(std::unique_ptr<Node> child)
{
	child->parent_ = this;
	children_.push_back(std::move(child));
}


// Draws all the children (and their children)
void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	drawSelf(target, states);
	drawChildren(target, states);
}


void Node::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
}


void Node::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const std::unique_ptr<Node>& child : children_)
	{
		child->draw(target, states);
	}
}


void Node::update(sf::Time deltaTime)
{
}


std::vector<const Node*> Node::getChildren() const
{
	std::vector<const Node*> children;

	for (const std::unique_ptr<Node>& child : children_)
	{
		children.push_back(child.get());
	}

	return children;
}
