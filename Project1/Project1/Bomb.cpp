#include "Bomb.h"
#include <iostream>
using namespace std;

Bomb::Bomb(int x, int y, float r)
{
	this->x = x/32;
	this->y = y/32;
	range = r;
	timePutClock.restart();
	bombSprite.setnew("Map/bomb.png", x+32, y+96);
	this->state = 0;
	maxRange[0] = 0; maxRange[1] = 0; maxRange[2] = 0; maxRange[3] = 0;
}

int Bomb::getPositionX()
{
	return x;
}

int Bomb::getPositionY()
{
	return y;
}

int Bomb::timeToExplode()
{
	if (timePutClock.getElapsedTime().asSeconds() > timeInSeconds) {
		return 1;
	}
	return 0;
}

void Bomb::drawFire(sf::RenderWindow*window, int* map)
{
	window->draw(bombSprite.getSprite());
	bombSprite.editPosition(x * 32 + 32, y * 32 + 96);
	window->draw(bombSprite.getSprite());
	for (int i = 0; i < maxRange[0]; i++) {
		bombSprite.editPosition(x * 32 + 32, y * 32 + 96 - (i+1) * 32);
		window->draw(bombSprite.getSprite());//up
	}
	for (int i = 0; i < maxRange[1]; i++) {
		bombSprite.editPosition(x * 32 + 32, y * 32 + 96 + (i+1) * 32);
		window->draw(bombSprite.getSprite());//down
	}
	for (int i = 0; i < maxRange[2]; i++) {
		bombSprite.editPosition(x * 32 + 32 - (i+1) * 32, y * 32 + 96);
		window->draw(bombSprite.getSprite());//left
	}
	for (int i = 0; i < maxRange[3]; i++) {
		bombSprite.editPosition(x * 32 + 32 + (i+1) * 32, y * 32 + 96);
		window->draw(bombSprite.getSprite());//right
	}
	bombSprite.editPosition(x * 32 + 32, y * 32 + 96);
}

int Bomb::explodeEnd()
{
	if (timePutClock.getElapsedTime().asSeconds() > explodeVis) {
		return 1;
	}
	return 0;
}

void Bomb::explode(int* map, std::vector <Box> &box, int chance, sf::Texture* texture, int* scoreN, int scorePerWall)
{
	if (state == 1) {
		return;
	}
	timePutClock.restart();
	state = 1;
	bombSprite.setnew("Map/bomb.png", x * 32 + 32, y * 32 + 96);//tutaj wrzucamy te ognie;
		for (int i = 1; i <= range; i++) {//g
			if (map[x + 1 + (y + 1 - i) * 31] == 0) {
				map[x + 1 + (y + 1 - i) * 31] = 0;
				maxRange[0]++;
			}
			else if(map[x + 1 + (y + 1 - i) * 31] == 2){
				*scoreN += scorePerWall;
				map[x + 1 + (y + 1 - i) * 31] = 0;
				box.push_back(Box());//+2 bo pomijamy puste 2 linie		
				box[box.size() - 1].setParam(chance/*chance zamiast 100*/, x, y + 2 - i, texture);
				if (box[box.size() - 1].getSucces() == 0) {
					box.pop_back();
				}
				else {
					box[box.size() - 1].setTextureP();
				}
				maxRange[0]++;
				break;
			}
			else {
				break;
			}
		}
		for (int i = 1; i <= range; i++) {//d
			if (map[x + 1 + (y + 1 + i) * 31] == 0) {
				maxRange[1]++;
			}
			else if (map[x + 1 + (y + 1 + i) * 31] == 2) {
				*scoreN += scorePerWall;
				map[x + 1 + (y + 1 + i) * 31] = 0;
				box.push_back(Box());//+2 bo pomijamy puste 2 linie			
				box[box.size() - 1].setParam(chance/*chance zamiast 100*/, x, y + 2 + i, texture);
				if (box[box.size() - 1].getSucces() == 0) {
					box.pop_back();
				}
				else {
					box[box.size() - 1].setTextureP();
				}
				maxRange[1]++;
				break;
			}
			else {
				break;
			}
		}
		for (int i = 1; i <= range; i++) {//l
			if (map[x + 1 - i + (y + 1) * 31] == 0) {
				map[x + 1 - i + (y + 1) * 31] = 0;
				maxRange[2]++;
			}
			else if (map[x + 1 - i + (y + 1) * 31] == 2) {
				*scoreN += scorePerWall;
				map[x + 1 - i + (y + 1) * 31] = 0;
				box.push_back(Box());//+2 bo pomijamy puste 2 linie			
				box[box.size() - 1].setParam(chance/*chance zamiast 100*/, x - i, y + 2, texture);
				if (box[box.size() - 1].getSucces() == 0) {
					box.pop_back();
				}
				else {
					box[box.size() - 1].setTextureP();
				}
				maxRange[2]++;
				break;
			}
			else {
				break;
			}
		}
		for (int i = 1; i <= range; i++) {//p
			if (map[x + 1 + i + (y + 1) * 31] == 0) {
				map[x + 1 + i + (y + 1) * 31] = 0;
				maxRange[3]++;
			}
			else if (map[x + 1 + i + (y + 1) * 31] == 2) {
				*scoreN += scorePerWall;
				map[x + 1 + i + (y + 1) * 31] = 0;
				box.push_back(Box());//+2 bo pomijamy puste 2 linie			
				box[box.size() - 1].setParam(chance/*chance zamiast 100*/, x + i, y + 2, texture);
				if (box[box.size() - 1].getSucces() == 0) {
					box.pop_back();
				}
				else {
					box[box.size() - 1].setTextureP();
				}
				maxRange[3]++;
				break;
			}
			else {
				break;
			}
		}
		for (int i = 0; i < 4; i++) {
			cout << "I: " << i << "R: " << maxRange[i] << endl;
		}
}

int Bomb::getState()
{
	return state;
}

sf::Sprite Bomb::getSprite()
{
	return bombSprite.getSprite();
}

int* Bomb::getMaxRange()
{
	return maxRange;
}

int Bomb::killPlayer(int pX, int pY, int frame, int dir, int maxFrame)
{
	//cout << "X: " << pX << " " << x << " Y: " << pY << " " << y << endl;
	//cout << "FRAMES: " << frame << " MAXFRAMES " << maxFrame << endl;
	if (frame >= maxFrame/2) {
		switch (dir) {
		case 1:
			pY--;
			break;
		case 2:
			pY++;
			break;
		case 3:
			pX--;
			break;
		case 4:
			pX++;
			break;
		}
	}
	//cout << "X: " << pX <<" "<< x << " Y: " << pY << " " << y << endl;
	if (pX == x) {//sprawdzenie gora dol
		if ((y - maxRange[0] <= pY && y >= pY) || (y + maxRange[1] >= pY && y <= pY)) {
			return 1;
		}
	} 
	if (pY == y) {//sprawdzenie lewo prawo
		if ((x - maxRange[2] <= pX && x >= pX) || (x + maxRange[3] >= pX && x <= pX)) {
			return 1;
		}
	}
	return 0;
}

int Bomb::checkBef(int* map, int dir, int act)
{
	//if (act == 1) { return 1;}
	switch (dir) {//g,d,l,p
	case 1:
		for (int i = act; i >= 1; i--) {
			if (map[x + 1 + (y + 1 - i) * 31] == 1) {
				return 0;
			}
		}
		break;
	case 2:
		for (int i = act; i >= 1; i--) {
			if (map[x + 1 + (y + 1 + i) * 31] == 1) {
				return 0;
			}
		}
		break;
	case 3:
		for (int i = act; i >= 1; i--) {
			if (map[x + 1 - i + (y + 1) * 31] == 1) {
				return 0;
			}
		}
		break;
	case 4:
		for (int i = act; i >= 1; i--) {
			if (map[x + 1 + i + (y + 1) * 31] == 1 /*Maksymalnie jeden kafelek niszczony, po prawej warunek || (map[x + 1 + i + (y + 1) * 31] == 2 && i != 1)*/) {
				return 0;
			}
		}
		break;
	}
	return 1;
}
