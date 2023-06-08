#pragma once
#include "DynamicTexture.h"
class Box
{
public:
	//Box(int, int, int);
	void setParam(int, int, int, sf::Texture*);
	sf::Sprite getBox();
	void checkPosition(int, int);
	int getSucces();
	void setTextureP();
	int getBoostType();
	int getX();
	int getY();
	//void drawBomb();
private:
	//ogarnac cale boxy, ich dzialanie. Nastepnie dodac przeciwnikow i ich algorytmike, ciekawea rzecz.
	//pozniej skonstruowac gorny pasek, przechodzenie lvl'i, animacje pozostale rzeczy i koniec :)
	sf::Texture texture;
	sf::Sprite sprite;
	int x = 0;
	int y = 0;
	int succes = 0;
	int boostType = 0;
};

