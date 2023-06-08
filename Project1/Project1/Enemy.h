#pragma once
#include "Bomb.h"
class Enemy
{
public:
	sf::Sprite getEnemy();
	void createEnemy(int, int*, sf::Texture*);
	void move(int*, int, int, std::vector <Box> &, int, std::vector <Bomb*> bomb, int range);
	void isBoxDestroy(std::vector <Box>&, int, int);
	int killPlayer(int, int, int, int, int);
	int getX();
	int getY();
	int getFrame();
	int getDir();
private:
	void moveTexture(int);
	int checkBombNearby(std::vector <Bomb*>, int);
	int checkAllDirIsBlocked(std::vector <Bomb*>, int*);
	void changePositionOnMap();
	int dif = 0;
	void checkStunEnd(int *);
	int x;
	int y;
	int death = 0;
	int czyMove = 0;
	int frame = 0;
	int actualDir = 0;
	int isBlocked = 0;
	DynamicTexture texture;
	int stun = 0;
	float stunTime = 2;
	sf::Clock stunClock;
};

