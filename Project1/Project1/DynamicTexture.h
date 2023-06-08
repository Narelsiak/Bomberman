#pragma once
#include "StaticTexture.h"
class DynamicTexture : public StaticTexture
{
public:
	void editRectangle(int, int, int, int);
	void editPosition(int, int);
	sf::IntRect getRectangle();
	sf::Vector2f getPosition();
};

