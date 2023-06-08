#include "Enemy.h"
#include <iostream>
using namespace std;
sf::Sprite Enemy::getEnemy()
{
	return texture.getSprite();
}

void Enemy::createEnemy(int diff, int* map, sf::Texture* tex)
{
	int randPos = (std::rand() % 651);
	for(;;){
		randPos = (std::rand() % 651);
		if (map[randPos] == 0) {
			x = randPos % 31;
			y = randPos / 31;
			if (x > 6 || y > 6) {
				break;
			}
		}
	}	
	dif = diff;
	map[randPos] = 9;
	texture.setNew(tex, x * 32, (y + 2) * 32);
	texture.editRectangle(0, 32, 32, 32);
}

void Enemy::move(int* map, int playerX, int playerY, std::vector <Box> &box, int chance, std::vector <Bomb*> bomb, int range)
{
	//todo: ogarnac kod tam gdzie jest syfiasty, czyli: tu, map
	int potentialStun = 0;
	int itsOK = 0;
	int randDir;
	int maxIteration = 0;
	if (czyMove == 0) {
		while (1) {
			isBlocked = 0;
			if (checkAllDirIsBlocked(bomb, map) == 0) {
				isBlocked = 1;
				break;
			}
			randDir = (std::rand() % 4) + 1;
			switch (randDir) {
			case 1:
				if (map[x+ (y - 1) * 31] != 1 && checkBombNearby(bomb, randDir) == 1) {
					if (map[x + (y - 1) * 31] == 2) potentialStun = 1;
					itsOK = 1;
				}
				break;
			case 2:
				if (map[x + (y + 1) * 31] != 1 && checkBombNearby(bomb, randDir) == 1) {
					if (map[x + (y + 1) * 31] == 2) potentialStun = 1;
					itsOK = 1;
				}
				break;
			case 3:
				if (map[x - 1 + (y) * 31] != 1 && checkBombNearby(bomb, randDir) == 1) {
					if (map[x - 1 + (y) * 31] == 2) potentialStun = 1;
					itsOK = 1;
				}
				break;
			case 4:
				if (map[x + 1 + (y) * 31] != 1 && checkBombNearby(bomb, randDir) == 1) {
					if (map[x + 1 + (y) * 31] == 2) potentialStun = 1;
					itsOK = 1;
				}
				break;
			}
			if (itsOK == 1) {
				switch (randDir) {
				case 1:
					if (abs(y - playerY)  < abs(y - 1 - playerY)) itsOK = 0;
					break;
				case 2:
					if (abs(y - playerY) < abs(y + 1 - playerY)) itsOK = 0;
					break;
				case 3:
					if (abs(x - playerX) < abs(x - 1 - playerX)) itsOK = 0;
					break;
				case 4:
					if (abs(x - playerX) < abs(x + 1 - playerX)) itsOK = 0;
					break;
				}
				//start nowo dodane
				int randomChance = (std::rand() % 100);
				if (randomChance > (chance * 2 - 20)) {
					for (int i = 0; i < bomb.size(); i++) {
						//cout << "Przeciwnik: " << x << " y " << y << " bomba: " << bomb[i]->getPositionX() << " y " << bomb[i]->getPositionY() << endl;
						if (bomb[i]->getPositionX() == x - 1 && bomb[i]->getState() == 0 && ((y - 1) >= bomb[i]->getPositionY() ? (y - 1) - bomb[i]->getPositionY() : bomb[i]->getPositionY() - (y - 1)) <= range) {
							if (randDir == 1 && y - 1 >= bomb[i]->getPositionY()) {//przeciwnik pod bomba
								if (map[x - 1 + (y) * 31] == 0 && checkBombNearby(bomb, 3) == 1) {
									randDir = 3; itsOK = 1;}
								if (map[x + 1 + (y) * 31] == 0 && checkBombNearby(bomb, 4) == 1) {
									randDir = 4; itsOK = 1;}
								if (map[x + (y + 1) * 31] == 0 && checkBombNearby(bomb, 2) == 1) {
									randDir = 2; itsOK = 1;}
								break;
							}
							else if (randDir == 2 && y - 1 <= bomb[i]->getPositionY()) {//przeciwnik nad bomba
								if (map[x - 1 + (y) * 31] == 0 && checkBombNearby(bomb, 3) == 1) {
									randDir = 3; itsOK = 1;}
								if (map[x + 1 + (y) * 31] == 0 && checkBombNearby(bomb, 4) == 1) {
									randDir = 4; itsOK = 1;}
								if (map[x + (y - 1) * 31] == 0 && checkBombNearby(bomb, 1) == 1) { 
									randDir = 1; itsOK = 1;}
								break;
							}
						}
						if (bomb[i]->getPositionY() == y - 1 && bomb[i]->getState() == 0 && ((x - 1) >= bomb[i]->getPositionX() ? (x - 1) - bomb[i]->getPositionX() : bomb[i]->getPositionX() - (x - 1)) <= range) {
							if (randDir == 3 && x - 1 >= bomb[i]->getPositionX()) {
								if (map[x + (y - 1) * 31] == 0 && checkBombNearby(bomb, 1) == 1) {
									randDir = 1; itsOK = 1;}
								if (map[x + (y + 1) * 31] == 0 && checkBombNearby(bomb, 2) == 1) {
									randDir = 2; itsOK = 1;}
								if (map[x + 1 + (y) * 31] == 0 && checkBombNearby(bomb, 4) == 1) {
									randDir = 4; itsOK = 1;}
								break;
							}
							else if (randDir == 4 && x - 1 <= bomb[i]->getPositionX()) {
								if (map[x + (y - 1) * 31] == 0 && checkBombNearby(bomb, 1) == 1) {
									randDir = 1; itsOK = 1;}
								if (map[x + (y + 1) * 31] == 0 && checkBombNearby(bomb, 2) == 1) {
									randDir = 2; itsOK = 1;}
								if (map[x - 1 + (y) * 31] == 0 && checkBombNearby(bomb, 3) == 1) {
									randDir = 3; itsOK = 1;}
								break;
							}							
						}
						//dotad chyba ok
						if (bomb[i]->getState() == 1) {
							cout << "PROBUJE UCIEKAC" << endl;
							if (abs(bomb[i]->getPositionX() - (x - 1)) <= 1) {
								if ((y - 1) > bomb[i]->getPositionY() && randDir == 1 && (y - 1) - range <= 1) {
									if (map[x - 1 + (y) * 31] == 0 && checkBombNearby(bomb, 3) == 1) { randDir = 3; itsOK = 1; }
									if (map[x + 1 + (y) * 31] == 0 && checkBombNearby(bomb, 4) == 1) { randDir = 4; itsOK = 1; }
									if (map[x + (y + 1) * 31] == 0 && checkBombNearby(bomb, 2) == 1) { randDir = 2; itsOK = 1; }
									break;
								}
								else if ((y - 1) < bomb[i]->getPositionY() && randDir == 2 && (y - 1) - range <= 1) {
									if (map[x - 1 + (y) * 31] == 0 && checkBombNearby(bomb, 3) == 1) { randDir = 3; itsOK = 1; }
									if (map[x + 1 + (y) * 31] == 0 && checkBombNearby(bomb, 4) == 1) { randDir = 4; itsOK = 1; }
									if (map[x + (y - 1) * 31] == 0 && checkBombNearby(bomb, 1) == 1) { randDir = 1; itsOK = 1; }
									break;
								}
							}
							else if (abs(bomb[i]->getPositionY() - (y - 1)) <= 1) {
								if ((x - 1) > bomb[i]->getPositionX() && randDir == 3 && (x - 1) - range <= 1) {
									if (map[x + (y - 1) * 31] == 0 && checkBombNearby(bomb, 1) == 1) { randDir = 1; itsOK = 1; }
									if (map[x + (y + 1) * 31] == 0 && checkBombNearby(bomb, 2) == 1) { randDir = 2; itsOK = 1; }
									if (map[x + 1 + (y) * 31] == 0 && checkBombNearby(bomb, 4) == 1) { randDir = 4; itsOK = 1; }
									break;
								}
								else if ((x - 1) < bomb[i]->getPositionX() && randDir == 4 && (x - 1) - range <= 1) {
									if (map[x + (y - 1) * 31] == 0 && checkBombNearby(bomb, 1) == 1) { randDir = 1; itsOK = 1; }
									if (map[x + (y + 1) * 31] == 0 && checkBombNearby(bomb, 2) == 1) { randDir = 2; itsOK = 1; }
									if (map[x - 1 + (y) * 31] == 0 && checkBombNearby(bomb, 3) == 1) { randDir = 3; itsOK = 1; }
									break;
								}
							}

						}
					}
					switch (randDir) {
					case 1:
						if (map[x + (y - 1) * 31] == 2) potentialStun = 1;
						break;
					case 2:
						if (map[x + (y + 1) * 31] == 2) potentialStun = 1;
						break;
					case 3:
						if (map[x - 1 + (y) * 31] == 2) potentialStun = 1;
						break;
					case 4:
						if (map[x + 1 + (y) * 31] == 2) potentialStun = 1;
					}
				}
				//koniec nowo dodane
				//todo tutaj sprawdzenie, czy bomba w poblizu - i losowanko
				if (itsOK == 0) {
					int randomChance = (std::rand() % 100);
					if (randomChance < (100 - chance)) itsOK = 1;
				}
			}
		if (itsOK == 1) break;
		potentialStun = 0;
		}
	}

	checkStunEnd(map);
	if (stun != 1 && isBlocked !=1) {
		if (potentialStun == 1) {
			stun = 1;
			stunClock.restart();
		}
		if (czyMove == 0 && frame == 0) {
			actualDir = randDir;
			czyMove = 1;
			moveTexture(randDir);
			frame++;
		}
		else if (czyMove == 1 && frame < 16) {
			moveTexture(actualDir);
			frame++;
		}
		else {
			isBoxDestroy(box, x, y);
			changePositionOnMap();
			frame = 0;
			czyMove = 0;
			move(map, playerX, playerY, box, chance, bomb, range);
		}
	}
}

void Enemy::checkStunEnd(int* map)
{
	if (stunClock.getElapsedTime().asSeconds() > stunTime && stun == 1) {
		stun = 0;
		switch (actualDir) {
		case 1:
			map[(y - 1) * 31 + x] = 0;
			break;
		case 2:
			map[(y + 1) * 31 + x] = 0;
			break;
		case 3:
			map[y * 31 + x - 1] = 0;
			break;
		case 4:
			map[y * 31 + x + 1] = 0;
			break;
		}
	}
}

void Enemy::isBoxDestroy(std::vector<Box>& box, int posX, int posY)
{
	for (int i = 0; i < box.size(); i++) {
		if (box[i].getX() == posX - 1 && box[i].getY() == posY - 1) {
			cout << "MA TO!" << endl;
			box.erase(box.begin() + i);
			break;
		}
	}
}

int Enemy::killPlayer(int pX, int pY, int dirP, int frameP, int maxFrameP)
{
	int tempX = x-1;
	int tempY = y-1;
	if (frameP >= maxFrameP / 2) {
		switch (dirP) {
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
	if (frame >= 16 / 2) {
		switch (actualDir) {
		case 1:
			tempY--;
			break;
		case 2:
			tempY++;
			break;
		case 3:
			tempX--;
			break;
		case 4:
			tempX++;
			break;
		}
	}
	if (tempX == pX && tempY == pY) {//sprawdzenie gora dol
		return 1;
	}
	return 0;
}

int Enemy::getX()
{
	return x;
}

int Enemy::getY()
{
	return y;
}

int Enemy::getFrame()
{
	return frame;
}

int Enemy::getDir()
{
	return actualDir;
}

void Enemy::moveTexture(int dir)
{
	int p = 2;
	switch (dir) {
	case 1:
		texture.editPosition(texture.getPosition().x, texture.getPosition().y - p);
		break;
	case 2:
		texture.editPosition(texture.getPosition().x, texture.getPosition().y + p);
		break;
	case 3:
		texture.editPosition(texture.getPosition().x - p, texture.getPosition().y);
		break;
	case 4:
		texture.editPosition(texture.getPosition().x + p, texture.getPosition().y);
		break;
	}
}

int Enemy::checkBombNearby(std::vector<Bomb*> bomb, int dir)
{
	for (int i = 0; i < bomb.size(); i++) {
		//cout << "Enemy x: " << x << " Enemy y: " << y << " bomb x: " << bomb[i]->getPositionX() << " bomb y: " << bomb[i]->getPositionY() << endl;
		switch (dir) {
		case 1:
			if (bomb[i]->getPositionX() == x - 1 && bomb[i]->getPositionY() == y - 2) { cout << "here09" << endl; return 0; }
			break;
		case 2:
			if (bomb[i]->getPositionX() == x - 1 && bomb[i]->getPositionY() == y) { cout << "here10" << endl; return 0;}
			break;
		case 3:
			if (bomb[i]->getPositionX() == x - 2 && bomb[i]->getPositionY() == y - 1) { cout << "here11" << endl; return 0;}
			break;
		case 4:
			if (bomb[i]->getPositionX() == x && bomb[i]->getPositionY() == y - 1) { cout << "here12" << endl; return 0; }
			break;
		}
	}
	return 1;
}

int Enemy::checkAllDirIsBlocked(std::vector<Bomb*> bomb, int* map)
{
	int dirBlockedArr[4] = { 0, 0, 0, 0 };
	if (map[x + (y - 1) * 31] == 1) { dirBlockedArr[0] = 1; }
	if (map[x + (y + 1) * 31] == 1) { dirBlockedArr[1] = 1; }
	if (map[x - 1 + (y) * 31] == 1) { dirBlockedArr[2] = 1; }
	if (map[x + 1 + (y) * 31] == 1) { dirBlockedArr[3] = 1; }

	if (checkBombNearby(bomb, 1) == 0) {
		dirBlockedArr[0] = 1; cout << "bomb1";
	}
	if (checkBombNearby(bomb, 2) == 0) {
		dirBlockedArr[1] = 1; cout << "bomb2";
	}
	if (checkBombNearby(bomb, 3) == 0) {
		dirBlockedArr[2] = 1; cout << "bomb3";
	}
	if (checkBombNearby(bomb, 4) == 0) {
		dirBlockedArr[3] = 1; cout << "bomb4";
	}
	for (int i = 0; i < 4; i++) {
		if (dirBlockedArr[i] == 0)
			return 1;
	}
	return 0;
}

void Enemy::changePositionOnMap()
{
	switch (actualDir) {
	case 1:
		y -= 1;
		break;
	case 2:
		y += 1;
		break;
	case 3:
		x -= 1;
		break;
	case 4:
		x += 1;
		break;
	}
}