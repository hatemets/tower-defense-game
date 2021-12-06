#include "../include/Message.hpp"
#include <iostream>

Message::Message(const std::string& msg, Type type)
    : message_(msg),
    messageBox_(sf::Vector2f(400.f, 100.f)),
    isActive_(false),
    type_(type)
{
    auto center = sf::Vector2f(WindowWidth / 2.f, WindowHeight / 2.f);


    /* if (type_ == Type::GameOver) */
    /* { */
    /*     text_.setFillColor(sf::Color::Red); */
    /*     text_.setCharacterSize(GameOverTextFontSize); */
    /* } */
    /* else */
    /* { */
    text_.setFillColor(sf::Color::White);
    /* } */

    messageBox_.setOrigin(messageBox_.getSize().x / 2.f, messageBox_.getSize().y / 2.f);
    messageBox_.setPosition(center.x, center.y);
    messageBox_.setFillColor(sf::Color(54, 87, 176));

    font_.loadFromFile("./include/fonts/SourceCodePro.ttf");

    text_.setString(msg);
    text_.setFont(font_);

    auto bounds = text_.getGlobalBounds();
    text_.setOrigin((bounds.width + bounds.left) / 2.f, (bounds.height + bounds.top) / 2.f);
    text_.setPosition(center.x, center.y - 5.f);
}

void Message::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(messageBox_, states);
    target.draw(text_, states);
}
