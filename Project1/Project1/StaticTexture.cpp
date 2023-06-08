#include "StaticTexture.h"
#include <iostream>
/*StaticTexture::StaticTexture(const char path[40], float positionX, float positionY)
{
//konstruktor nieudany, bo nie mozna uzywac w tablicy?
    textureLoad(path);
    setTexture();   
    setPosition(positionX, positionY);
}*/
void StaticTexture::setnew(const char path[40], float positionX, float positionY)
{
    textureLoad(path);
    setTexture();
    setPosition(positionX, positionY);
}

void StaticTexture::setNew(sf::Texture* tex, float positionX, float positionY)
{
    sprite.setTexture(*tex);
    setPosition(positionX, positionY);
}

sf::Sprite StaticTexture::getSprite()
{
    return sprite;
}

sf::Sprite* StaticTexture::getSpriteP()
{
    return &sprite;
}

void StaticTexture::textureLoad(const char path[40])
{
    if (!texture.loadFromFile(path))
    {
        // error...
    }
}

void StaticTexture::setTexture()
{
    sprite.setTexture(texture);
}

void StaticTexture::setPosition(float positionX, float positionY)
{
    sprite.setPosition(sf::Vector2f(positionX, positionY)); // absolute position
}
