#pragma once
#include "Box.h"
class Bomb
{
public:
	Bomb(int, int, float);
	int getPositionX();
	int getPositionY();
	int timeToExplode();
	void drawFire(sf::RenderWindow*, int*);
	int explodeEnd();
	void explode(int *, std::vector <Box>&, int, sf::Texture *, int*, int);
	int getState();
	sf::Sprite getSprite();
	int* getMaxRange();
	int killPlayer(int, int, int, int, int);
private:
	int checkBef(int*, int, int);
	int state;
	const float explodeVis = 2.5f;
	int x;
	int y;
	float range;
	const float timeInSeconds = 5.f;
	//sf::Time timePut;
	sf::Clock timePutClock;
	DynamicTexture bombSprite;
	int maxRange[4];//0-gora,1-dol,2-lewo,3-prawo
};

