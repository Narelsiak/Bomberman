#pragma once
#include <SFML/Graphics.hpp>
#include "DynamicTexture.h"
#include <iostream>
#include "Bomb.h"
class Player
{
public:
	void init();
	void changeDirection(sf::Keyboard::Key);
	void move(sf::RenderWindow* window, int*map);
	void stop();
	void restart();
	sf::Sprite getSprite();
	void setLife(int);
	int getLife();
	int getMove();
	int getFrame();
	int getDirectionChange();
	void setMove(int);
	void setStopStatus(int);
	int getStopStatus();
	void setFrame(int);
	void setDirectionChange(int);
	int getBombLimit();
	void setBombLimit(int);
	int getPositionX();
	int getPositionY();
	int checkCollision(int*, std::vector <Bomb*>, int);
	int getTemporaryInvincible();
	void setTemporaryInvincible(int);
	int checkInvincibleEnd();
	int getDir();
	int getDeath();
	void setDeath(int);
private:
	int temporaryInvincible = 0;
	int lifes = 0;
	int death = 0;
	int bombLimit = 2;
	int klatka = 0;
	bool czyMove = 0;
	bool changeDir = 0;
	int dir = 0; //1-gora, 2-dol, 3-lewo, 4-prawo
	int x = 0;
	int y = 0;
	int stopStatus = 0;
	sf::Texture texturePlayer;
	sf::Sprite player;
	DynamicTexture player1;
	void changeCord();
	void loadSprite();
	void editPosition(sf::RenderWindow* window, sf::Keyboard::Key);
	int checkAllIsBlocked(int*, int, int);

	sf::Clock invincibleClock;
	int frameInvi = 0;
};