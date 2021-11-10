#ifndef RESOURCE_HOLDER_HPP
#define RESOURCE_HOLDER_HPP

#include <SFML/Graphics.hpp>
#include "auxiliary/ResourceIdentifiers.hpp"
#include <map>
#include <memory>
#include <cassert>

// TODO: Make the class abstract without breaking the system
template <typename Resource, typename Identifier>
class GeneralResourceHolder
{
	public:
		Resource& get(Identifier id);
		const Resource& get(Identifier id) const;

	public:
		std::map<Identifier, std::unique_ptr<Resource>> resources_;
};

// Resource holder for resources loaded from files
template <typename Resource, typename Identifier>
class ResourceHolder : public GeneralResourceHolder<Resource, Identifier>
{
	public:
		void load(Identifier id, const std::string& filename);
};

// NOTE: Identifier is subject to change. ResourceIdentifiers file contents might be
// grouped into smaller bunches of identifiers to improve readability.
template <typename Identifier>
class ButtonHolder : public GeneralResourceHolder<sf::RectangleShape, Identifier>
{
	public:
		void load(Identifier id);
};

#include "ResourceHolder.inl"

#endif
