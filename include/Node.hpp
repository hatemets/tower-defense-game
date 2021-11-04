#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

// Node is a tree consisting of parents and childrens (branches)
class Node :
	public sf::Drawable,
	public sf::Transformable
{
	public:
		Node();

	public:
		void addChild(std::unique_ptr<Node> child);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
		virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void update(sf::Time deltaTime);

	private:
		Node* parent_;
		std::vector<std::unique_ptr<Node>> children_;
};

#endif
