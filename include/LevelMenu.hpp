#ifndef LEVEL_MENU_HPP
#define LEVEL_MENU_HPP

#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include "ResourceHolder.hpp"
#include "auxiliary/ResourceIdentifiers.hpp"
#include "Mode.hpp"
#include "Button.hpp"
#include "GameData.hpp"

// Controls the turrets, enemies, map
class LevelMenu : public Mode
{
	public:
		LevelMenu(sf::RenderWindow& window, std::shared_ptr<GameData> gameData);
		virtual void update(sf::Time deltaTime) final;
	
	private:
		enum class Layers
		{
			Background,
			Buttons,
			// total count of enum values
			TotalCount	 
		};

	private:
		virtual void loadResources() final;
		virtual void createScene() final;
		virtual void addButtons() override;
		virtual void addBackground() override;

	private:
		ResourceHolder<sf::Texture, Textures::ID> textures_;
		std::shared_ptr<GameData> gameData_;
};

#endif
