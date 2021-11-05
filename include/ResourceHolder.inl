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
	std::unique_ptr<Resource> resource = std::make_unique<Resource>();

	if (!resource->loadFromFile(filename))
	{
		throw std::runtime_error("ResourceHolder: loading the file failed: " + filename);
	}

	// Move (not copy) the resource to resources map
	// NOTE: "this" keyword is necessary in this context, since otherwise the
	// compiler would assume that resources_ should be a global variable
	auto inserted = this->resources_.insert(std::make_pair(id, std::move(resource)));

	// If the resource does not exist, halt the program
	// NOTE: Remove after testing
	assert(inserted.second);
}


// ShapeHolder
template <typename Identifier>
void ShapeHolder<Identifier>::load(Identifier id)
{
	using namespace Resources;

	switch (id)
	{
		// Rectangular buttons
		case ID::StartButton:
		case ID::QuitButton:
			{
				auto res = std::make_unique<sf::RectangleShape>();
				this->resources_.insert(std::make_pair(id, std::move(res)));
				break;
			}
			// Round butttons
		case ID::PauseButton:
			{
				auto res = std::make_unique<sf::CircleShape>();
				this->resources_.insert(std::make_pair(id, std::move(res)));
				break;
			}
		default:
			{
				throw std::runtime_error("ResourceHolder: Identifier did not match any type");
			}
	}
}
