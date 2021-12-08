#include "../include/Button.hpp"
<<<<<<< HEAD

Button::Button(ButtonData attributes)
{
=======
#include "../include/auxiliary/constants.hpp"
#include <array>

#include <iostream>

Button::Button(const std::string& text, ResourceHolder<sf::Font, Fonts::ID>& fonts, ButtonHolder<Buttons::ID>& resources, Buttons::ID buttonID, int charCount)
	: button_(resources.get(buttonID)),
	type_(buttonID),
    // Uneven or even number of characters in the string
    isEven(text.length() % 2 == 0)
{
    std::string mainText = text;

    const float ButtonPaddingY = 30.f;

    // Add spaces to both sides to even out the changes in button sizes
    while (mainText.length() < (std::size_t)charCount)
    {
        mainText = " " + mainText + " ";

        // Account for words with even no. of letters
        if (mainText.length() - charCount == 0 && isEven)
        {
            mainText += " ";
        }
    }

	text_.setFont(fonts.get(Fonts::ID::SourceCodePro));
	text_.setString(mainText);

	// Set the scale of the text
	// This effectively sets the size of the button as well
	text_.setScale(ButtonScalar, ButtonScalar);
	text_.setStyle(sf::Text::Bold);

	auto textBounds = text_.getLocalBounds();

	text_.setOrigin((textBounds.width + textBounds.left) / 2.f, (textBounds.height + textBounds.left) / 2.f);

	button_.setSize(sf::Vector2f(textBounds.width + textBounds.left, textBounds.height + textBounds.top + ButtonPaddingY));
	button_.setOrigin((textBounds.width - textBounds.left) / 2.f, (textBounds.height - textBounds.top + ButtonPaddingY) / 2.f);

	button_.setFillColor(sf::Color(PrimaryColor[0], PrimaryColor[1], PrimaryColor[2]));
	text_.setFillColor(sf::Color(SecondaryColor[0], SecondaryColor[1], SecondaryColor[2]));
}


void Button::setPosition(float x, float y)
{
	text_.setPosition(x, y);
	button_.setPosition(text_.getPosition());

    if (isEven)
    {
        // Adjust for the extra space
        text_.move(sf::Vector2f(10.f, 0.f));
    }
}


void Button::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(button_, states);
	target.draw(text_, states);
>>>>>>> layout
}
