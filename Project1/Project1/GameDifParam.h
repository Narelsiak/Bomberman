#pragma once
class GameDifParam
{
public:
	void setParametr(int);
	void difActuAfterComplete(int);

	int getDif();
	int getLife();
	int getBombRange();
	int getEnemyNumber();
	int getBombLimit();
	float getPlayerSpeed();
	float getEnemySpeed();
	int getPokrycie();
	int getChanceToBoost();
	int getLevel();
	int getChanceToChangeDir();
	int getScorePerWall();
	int getScorePerEnemy();
private:
	int dif = 0;
	int life = 0;
	int bombRange = 0;
	int bombLimit = 0;
	int enemyNumber = 0;
	float playerSpeed = 0;
	float enemySpeed = 0;
	int pokrycie = 0;//w %
	int boostChance = 0;
	int chanceToChangeDir = 0;
	int scorePerWall = 0;
	int scorePerEnemy = 0;
	int level = 1;
};

