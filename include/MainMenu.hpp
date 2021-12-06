#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include "ResourceHolder.hpp"
#include "auxiliary/ResourceIdentifiers.hpp"
#include "Mode.hpp"
#include "Button.hpp"

// Controls the turrets, enemies, map
class MainMenu : public Mode
{
	public:
        MainMenu(sf::RenderWindow& window, std::shared_ptr<GameData> gameData);
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
};

#endif
