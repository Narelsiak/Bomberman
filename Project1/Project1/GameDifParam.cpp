#include "GameDifParam.h"
#include <iostream>
void GameDifParam::setParametr(int diff) {
	switch (diff) {
	case 0:
		dif = 0;
		life = 3;
		bombRange = 3;
		bombLimit = 2;
		enemyNumber = 1;
		playerSpeed = 1.f / 20;//20
		enemySpeed = 1.f / 18;//18
		pokrycie = 25;
		boostChance = 40;
		chanceToChangeDir = 15;
		scorePerWall = 2;
		scorePerEnemy = 5;
		break;
	case 1:
		dif = 1;
		life = 2;
		bombRange = 2;
		bombLimit = 1;
		enemyNumber = 1;
		playerSpeed = 1.f / 20;
		enemySpeed = 1.f / 22;
		pokrycie = 30;
		boostChance = 30;
		chanceToChangeDir = 25;
		scorePerWall = 2;
		scorePerEnemy = 10;
		break;
	case 2:
		dif = 2;
		life = 1;
		bombRange = 1;
		bombLimit = 1;
		enemyNumber = 2;
		playerSpeed = 1.f / 20;
		enemySpeed = 1.f / 25;
		pokrycie = 35;
		boostChance = 20;
		chanceToChangeDir = 35;
		scorePerWall = 2;
		scorePerEnemy = 20;
		break;
	}
	level = 1;
}
void GameDifParam::difActuAfterComplete(int dif)
{
	int perceptibility;
	perceptibility = dif == 0 ? 3 : dif == 1 ? 2 : 1;
	if (level % perceptibility == 0) {
		enemyNumber += 1;
		if (pokrycie < 57) {
			pokrycie += 2;
		}
		if (chanceToChangeDir < 60) {
			chanceToChangeDir += 2;
		}
		//enemySpeed += ;
		//playerSpeed -= ;
	}
	level++;
}

int GameDifParam::getDif()
{
	return dif;
}

int GameDifParam::getLife()
{
	return life;
}

int GameDifParam::getBombRange()
{
	return bombRange;
}

int GameDifParam::getEnemyNumber()
{
	return enemyNumber;
}

int GameDifParam::getBombLimit()
{
	return bombLimit;
}

float GameDifParam::getPlayerSpeed()
{
	return playerSpeed;
}

float GameDifParam::getEnemySpeed()
{
	return enemySpeed;
}

int GameDifParam::getPokrycie()
{
	return pokrycie;
}

int GameDifParam::getChanceToBoost()
{
	return boostChance;
}

int GameDifParam::getLevel()
{
	return level;
}

int GameDifParam::getChanceToChangeDir()
{
	return chanceToChangeDir;
}

int GameDifParam::getScorePerWall()
{
	return scorePerWall;
}

int GameDifParam::getScorePerEnemy()
{
	return scorePerEnemy;
}
