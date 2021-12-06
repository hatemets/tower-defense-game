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
        enum class Type
        {
            Regular,
            GameOver
        };

    public:
        Message(const std::string& msg, Type type = Type::Regular);
        virtual void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const final;

        void changeMessage(const std::string& newMsg) { message_ = newMsg; text_.setString(message_); }
        const std::string& getMessage() { return message_; }
        bool isActive() { return isActive_; }
        void setActive(bool val) { isActive_ = val; }

    private:
        std::string message_;
        sf::RectangleShape messageBox_;
        bool isActive_;
        sf::Text text_;
        sf::Font font_;
        Type type_;
};


#endif
