#include "DynamicTexture.h"
#include <iostream>
void DynamicTexture::editRectangle(int a, int b, int c, int d)
{	
	getSpriteP()->setTextureRect(sf::IntRect(a, b, c, d));
}

void DynamicTexture::editPosition(int a, int b) 
{
	getSpriteP()->setPosition(a, b);
}

sf::IntRect DynamicTexture::getRectangle()
{
	return getSpriteP()->getTextureRect();
}

sf::Vector2f DynamicTexture::getPosition()
{
	return getSpriteP()->getPosition();
}

