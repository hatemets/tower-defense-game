#ifndef RESOURCE_HOLDER_HPP
#define RESOURCE_HOLDER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <cassert>
#include "auxiliary/Button.hpp"

template <typename Resource, typename Identifier>
class ResourceHolder
{
	public:
		void load(Identifier id, const std::string& filename);
		void load(sf::Vector2f size, sf::Color color, const std::string& text);

		Resource& get(Identifier id);
		const Resource& get(Identifier id) const;

	private:
		std::map<Identifier, std::unique_ptr<Resource>> resources_;
};

#include "ResourceHolder.inl"

#endif
