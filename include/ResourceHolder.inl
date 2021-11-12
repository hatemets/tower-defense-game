template <typename Resource, typename Identifier>
Resource& GeneralResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = this->resources_.find(id);

	assert(found != this->resources_.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& GeneralResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = this->resources_.find(id);

	assert(found != this->resources_.end());

	return *found->second;
}

// Texture and FontHolder
template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	// Allocate memory for the resource
	auto res = std::make_unique<Resource>();

	if (!res->loadFromFile(filename))
	{
		throw std::runtime_error("ResourceHolder: loading the file failed: " + filename);
	}

	// Move (not copy) the resource to resources map
	// NOTE: "this" keyword is necessary in this context, since otherwise the
	// compiler would assume that resources_ should be a global variable
	this->resources_.insert(std::make_pair(id, std::move(res)));
}


// ButtonHolder
template <typename Identifier>
void ButtonHolder<Identifier>::load(Identifier id)
{
	auto res = std::make_unique<sf::RectangleShape>();

	this->resources_.insert(std::make_pair(id, std::move(res)));
}
