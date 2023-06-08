#pragma once
#include <SFML/Graphics.hpp>
class StaticTexture
{
public:
	//StaticTexture(const char path[40], float positionX, float positionY);
     void setnew(const char path[40], float positionX, float positionY);
	 void setNew(sf::Texture*, float positionX, float positionY);
	 sf::Sprite getSprite();
	 sf::Sprite * getSpriteP();
private:
	sf::Sprite sprite;
	sf::Texture texture;
	void textureLoad(const char path[40]);
	void setTexture();
	void setPosition(float positionX, float positionY);
};