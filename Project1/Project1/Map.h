#pragma once
using namespace std;
#include "Player.h"
#include "Tiles.h"
#include "GameDifParam.h"
#include "ActiveBoost.h"
#include "Enemy.h"
#include "SFML/Graphics.hpp"
//random
#include <ctime>
#include <cstdlib>
class Map
{
public:
	void game(sf::RenderWindow*, GameDifParam*);
	void mainLoop(sf::RenderWindow*);
private:
	void checkUnder();
	void checkChanges();
	void checkPlayerContinueMove(sf::RenderWindow *);
	void events(sf::RenderWindow*);

	void clockFps(sf::RenderWindow*);
	void createMap();
	void drawBomb(sf::RenderWindow*);
	void drawBox(sf::RenderWindow*);
	void drawTopPanel(sf::RenderWindow*);
	void createTopPanel();
	void checkSomeoneLostLife(int);
	void gameEnd();
	void pauseF(sf::RenderWindow *);
	void drawScoreAndExit(sf::RenderWindow *);
	void loadingScreen(sf::RenderWindow *);
	int breakGame = 0;
	int pause = 0;
	int loading = 1;
	sf::Keyboard::Key lastKey;
	sf::Keyboard::Key nextKey;

	//panel
	vector <DynamicTexture> boostPanel;
	vector <StaticText> timeBoostPanel;
	vector <ActiveBoost> boosty;
	vector <StaticText> score;
	int scoreNumber = 0;

	vector <DynamicTexture> life;
	StaticText lifeText;
	sf::Texture lifeTexture;
	//panel
	//enemy
	vector <Enemy> enemy;
	sf::Texture enemyTexture;
	//enemy
	sf::Clock clock;
	sf::Time time;
	sf::Font font;
	sf::Text fps;
	std::string string1;
	
	vector <Bomb*> bomb;
	vector <Box> box;
	sf::Texture textureBoost;
	Player player1;
	sf::Clock clockMove;
	sf::Clock clockEnemy;	
	int bombChecked = 0;

	GameDifParam *gameParam;
	Tiles tile;
};

