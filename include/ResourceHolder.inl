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


<<<<<<< HEAD
template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, ButtonData::Shape shape)
{
	// Allocate memory for the resource
	std::unique_ptr<Resource> resource = std::make_unique<Resource>();

	if (!resource->loadFromFile(filename))
	{
		throw std::runtime_error("ResourceHolder load fail: " + filename);
	}

	// Move (not copy) the resource to resources map
	auto inserted = resources_.insert(std::make_pair(id, std::move(resource)));

	// If the resource does not exist, halt the program
	assert(inserted.second);
}


template <typename Resource, typename Identifier>
void void ResourceHolder<Resource, Identifier>::load(Button button)
=======
// ButtonHolder
template <typename Identifier>
void ButtonHolder<Identifier>::load(Identifier id)
>>>>>>> layout
{
	auto res = std::make_unique<sf::RectangleShape>();

	this->resources_.insert(std::make_pair(id, std::move(res)));
}
