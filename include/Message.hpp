#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "ResourceHolder.hpp"
#include "auxiliary/constants.hpp"
#include "Node.hpp"
#include "Button.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

using namespace Resources;

class Message : public Node
{
    public:
        Message(const std::string& msg, ResourceHolder<sf::Font, Fonts::ID>& fonts, ButtonHolder<Buttons::ID>& buttonShapes);
            virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const final;

        void changeMessage(const std::string& newMsg) { message_ = newMsg; text_.setString(message_); }
        const std::string& getMessage() { return message_; }
        bool isActive() { return isActive_; }
        void toggleActivation() { isActive_ = !isActive_; }

    private:
        std::string message_;
        std::unique_ptr<Button> button_;
        sf::Text text_;
        sf::RectangleShape messageBox_;
        bool isActive_;
};


#endif
