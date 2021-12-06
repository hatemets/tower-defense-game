#include "../include/Message.hpp"

Message::Message(const std::string& msg, ResourceHolder<sf::Font, Fonts::ID>& fonts, ButtonHolder<Buttons::ID>& buttonShapes_, ButtonHolder<Buttons::ID>& resources, Buttons::ID buttonID)
    : message_(msg),
    button_(std::make_unique<Button>("OK", fonts, resources, buttonID, 4)),
    text_(),
    messageBox_(sf::Vector2f(200.f, 150.f)),
    isActive_(false)
{
    // Text
    text_.setFont(fonts.get(Fonts::ID::SourceCodePro));
    text_.setFillColor(sf::Color::White);
    text_.setString(msg);

    auto bounds = text_.getGlobalBounds();
    text_.setOrigin((bounds.width + bounds.left) / 2.f, (bounds.height + bounds.top) / 2.f);
    text_.setPosition(WindowWidth / 2.f, WindowHeight / 2.f);


    // Box
    messageBox_.setOrigin(messageBox_.getSize().x / 2.f, messageBox_.getSize().y / 2.f);
    messageBox_.setPosition(WindowWidth / 2.f, WindowHeight / 2.f);

    messageBox_.setFillColor(sf::Color(54, 87, 176));
}

void Message::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(messageBox_, states);

    // These should not overlap
    target.draw(text_, states);
    button_->drawSelf(target, states);
}
