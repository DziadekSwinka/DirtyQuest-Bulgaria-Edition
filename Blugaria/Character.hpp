#ifndef CHARACTER_HPP_INCLUDED
#define CHARACTER_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "json.hpp"
#include "FrameTime.h"

#include "Background.hpp"

class character
{
private:
    sf::RenderWindow &window;
    sf::Sprite sprite;
    sf::Texture txt;
    using json=nlohmann::json;
    json j;
public:
    character(sf::RenderWindow &window1):window(window1)
    {
        background::loadJSON(&j);
        txt.loadFromFile(j["character"]);
        sprite.setTexture(txt);
        sprite.setScale(0.3,0.3);
        sprite.setOrigin(txt.getSize().x/2,txt.getSize().y/2);
        sprite.setPosition(window.getSize().x/2,800);
    }
    void Update()
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)||
           sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            //animacja ruchu
        }
        window.draw(sprite);
    }
};

#endif // CHARACTER_HPP_INCLUDED