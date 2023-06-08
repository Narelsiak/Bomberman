#include "Box.h"
#include <iostream>
//dodatkowa bomba, szybsze chodzenie, niesmiertelnosc, przechodzenie przez sciany
//wszystkie czasowe
//duszek zjada boosty, niszczy je
//sposob losowania? Jedno? dwa? jedno - od razu co, dwa - czy boost i jaki
//bomba 20%, chodzenie 15%, niesmiertenosc 10%, sciany 5% - do 100 --- zgadza sie
void Box::setParam(int chance, int posX, int posY, sf::Texture * texture)
{
	std::cout << "POZYCJA BOOSTA: " << posX <<"Y: "<< posY << std::endl;
	x = posX;
	y = posY;
	//srand(std::time(NULL));
	//losujemy liczbe
	int randomInt = (std::rand() % 100); //0-99
	if (randomInt < chance) {
		//wtedy losujemy
		randomInt = (std::rand() % 100);
		std::cout << "WYLOSOWASNO: " << randomInt << std::endl;
		if (randomInt < 35) {
			succes = 1;
			boostType = 0;
			//bomba
		}
		else if (randomInt < 70) {
			//chodzenie
			succes = 1;
			boostType = 1;
		}
		else if (randomInt < 80) {
			//niesmiertelnosc
			succes = 1;
			boostType = 2;
		}
		else {
			//sciany
			succes = 1;
			boostType = 3;
		}
	}
	if (succes == 1) {
		//dodanie tekstury
		sprite.setPosition(sf::Vector2f((x + 1) * 32, (y + 1) * 32));
		sprite.setTexture(*texture);
	}
}

sf::Sprite Box::getBox()
{
	return sprite;
}

void Box::checkPosition(int posX, int posY)
{
}

int Box::getSucces()
{
	return succes;
}

void Box::setTextureP()
{
	switch (boostType) {
	case 0:
		sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
		break;
	case 1:
		sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
		break;
	case 2:
		sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
		break;
	case 3:
		sprite.setTextureRect(sf::IntRect(96, 0, 32, 32));
		break;
	}
}

int Box::getBoostType()
{
	return boostType;
}

int Box::getX()
{
	return x;
}

int Box::getY()
{
	return y - 2;
}
