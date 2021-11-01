template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
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
{
	std::unique_ptr<sf::RectangleShape> resource = std::make_unique<sf::RectangleShape>(button.size);
	resource.get()->setColor(button.color);
}


template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = resources_.find(id);

	assert(found != resources_.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = resources_.find(id);

	assert(found != resources_.end());

	return *found->second;
}

