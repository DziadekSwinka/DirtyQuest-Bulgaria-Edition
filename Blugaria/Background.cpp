#include "Background.hpp"

float background::position=0;
float background::backgroundPosition={0.f};
bool background::isJSONLoaded=false;

background::background(sf::RenderWindow &window1):window(window1)
{
    loadJSON(&j);
    txt.resize(2);
    type=Intro;
    clock.restart();
    txt[0].loadFromFile(j["introBack"]);
    txt[1].loadFromFile(j["introFront"]);
    Back.setTexture(txt[0]);
    Front.setTexture(txt[1]);
    Front.setColor(sf::Color(225,225,225,0));
}
    background::background(sf::RenderWindow &window1,std::string s):window(window1)
{
    loadJSON(&j);
    txt.resize(NumberOfTextures);
    sprites.resize(16);
    tiles.resize(16);
    type=MainGame;
    clock.restart();
    for(long long unsigned int i=0;i<txt.size();i++)
    {
        txt[i].loadFromFile(j["houses"][i]);
    }
    Stxt.loadFromFile(j["street"]);
    Btxt.loadFromFile(j["background"]);
    for(long long unsigned int i=0;i<tiles.size();i++)
        tiles[i].setTexture(Stxt);
    Background.setTexture(Btxt);
    Background.setPosition(0,638);
    Background.setScale(0.11,0.05);
    for(long long unsigned int i=0;i<sprites.size();i++)
    {
        sprites[i].setTexture(txt[i%NumberOfTextures]);
        sprites[i].setScale(0.1,0.1);
    }
    position=0;
    width=[](std::vector<sf::Texture>&txt)
    {
        float total={0.f};
        for(long long unsigned int i=0;i<txt.size();i++)
            total+=txt[i].getSize().x;
        return (total*0.1);
    }(txt);
    backgroundPosition=-width;
}
void background::Update(double delta)
{
    switch(type)
    {
    case 0:
        updateIntro(delta);
        break;
    case 1:
        updateGame(delta);
        break;
    default:
        throw;
    }
}

void background::updateIntro(float delta)
{
    window.draw(Back);
    if(clock.getElapsedTime().asSeconds()>10)
    {
        Front.setColor(sf::Color(255,255,255,alpha));
        if(alpha<255)
            alpha+=3*delta;
        window.draw(Front);
    }
}
void background::Left(float S,float delta)
{
    backgroundPosition-=S*delta;
    if(backgroundPosition<-width)
        backgroundPosition+=width;
}
void background::Right(float S,float delta)
{
    backgroundPosition+=Speed*delta;
    if(backgroundPosition>window.getSize().x-width)
        backgroundPosition-=width;
}
void background::updateGame(float delta)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && isEscape==false && isAlive==true && isQuiz==false)
    {
        position-=Speed*delta;
        Left(Speed,delta);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)  && isEscape==false && isAlive==true && isQuiz==false)
    {
        position+=Speed*delta;
        Right(Speed,delta);
    }
    for(long long unsigned int i=0;i<tiles.size();i++)
    {
        tiles[i].setPosition(backgroundPosition+i*Stxt.getSize().x*tiles[i].getScale().x,760);
        window.draw(tiles[i]);
    }
    window.draw(Background);
    for(long long unsigned int i=0;i<sprites.size();i++)
    {
        switch(i%NumberOfTextures)
        {
        case 0:
            sprites[i].setPosition(backgroundPosition+int(i/NumberOfTextures)*width,600);
            break;
        case 1:
            sprites[i].setPosition(backgroundPosition+txt[0].getSize().x*sprites[0].getScale().x+(width*((int)i/NumberOfTextures)),670);
            break;
        case 2:
            sprites[i].setPosition(backgroundPosition+txt[1].getSize().x*sprites[1].getScale().x+txt[0].getSize().x*sprites[0].getScale().x+(width*((int)i/NumberOfTextures)),500);
            break;
        case 3:
            sprites[i].setPosition(backgroundPosition+txt[2].getSize().x*sprites[2].getScale().x+txt[1].getSize().x*sprites[1].getScale().x+txt[0].getSize().x*sprites[0].getScale().x
                    +(width*((int)i/NumberOfTextures)),620);
            break;
        case 4:
            sprites[i].setPosition(backgroundPosition+txt[3].getSize().x*sprites[3].getScale().x+txt[2].getSize().x*sprites[2].getScale().x+txt[1].getSize().x*sprites[1].getScale().x
                    +txt[0].getSize().x*sprites[0].getScale().x+(width*((int)i/NumberOfTextures)),590);
            break;
        case 5:
            sprites[i].setPosition(backgroundPosition+txt[4].getSize().x*sprites[4].getScale().x+txt[3].getSize().x*sprites[3].getScale().x+txt[2].getSize().x*sprites[2].getScale().x
                    +txt[1].getSize().x*sprites[1].getScale().x+txt[0].getSize().x*sprites[0].getScale().x+(width*((int)i/NumberOfTextures)),630);
            break;
        case 6:
            sprites[i].setPosition(backgroundPosition+txt[5].getSize().x*sprites[5].getScale().x+txt[4].getSize().x*sprites[4].getScale().x+txt[3].getSize().x*sprites[3].getScale().x
                    +txt[2].getSize().x*sprites[2].getScale().x+txt[1].getSize().x*sprites[1].getScale().x+txt[0].getSize().x*sprites[0].getScale().x+(width*((int)i/NumberOfTextures)),590);
            break;
        default:
            break;
        }
        window.draw(sprites[i]);
    }
}
