#include "Map.h"
#include <string>
//powrzucac zmienne z param tam gdzie trzeba, na pewno szansa na loot
void Map::game(sf::RenderWindow* window, GameDifParam *param){   
    gameParam = param;
    scoreNumber = 0;
    cout << "RANGE: " << gameParam->getBombRange() << endl;
            //licznik fps
    if (!font.loadFromFile("Fonts/OpenSans-Light.ttf")) {
    }
    if (!textureBoost.loadFromFile("Map/boost.png")){
    }
    if (!lifeTexture.loadFromFile("Map/hearth.png")) {
    }
    if (!enemyTexture.loadFromFile("Map/enemy1.png")) {
    }

    /* (int i = 0; i < 20; i++) {
        gameParam->difActuAfterComplete(gameParam->getDif());
    }*/

    createTopPanel();
    fps.setFont(font);
    fps.setFillColor(sf::Color::Red);
    fps.setPosition(0.f, 0.f);

    player1.init();
    player1.setLife(gameParam->getLife());
    cout << "DIFFFE" << gameParam->getDif() << endl;
    createMap();
    mainLoop(window);
}
void Map::loadingScreen(sf::RenderWindow * window)
{
    sf::Clock loadClock;
    loadClock.restart();
    sf::RectangleShape filter(sf::Vector2f(31 * 32, 23 * 32));
    filter.setFillColor(sf::Color(0, 0, 0, 5));
    sf::Text loadText("Loading...", font, 25);
    loadText.setPosition((31 * 32) / 2 - loadText.getGlobalBounds().width / 2, (32 * 23) / 2);
    while (loading == 1) {
        window->clear();
        window->draw(filter);
        window->draw(loadText);
        window->display();
        if (loadClock.getElapsedTime().asSeconds() > 3) {
            window->clear();
            loading = 0;
            break;
        }
    }
}
void Map::mainLoop(sf::RenderWindow* window)
{
    while (window->isOpen() && breakGame == 0) {
        if (pause == 1) {
            pauseF(window);
        }
        if (loading == 1) {
            loadingScreen(window);
        }
        window->clear();
        checkPlayerContinueMove(window);

        events(window);
        window->draw(tile);
        clockFps(window);
        drawBox(window);
        if (player1.checkInvincibleEnd() == 1) window->draw(player1.getSprite());
        drawTopPanel(window);

        for (int i = 0; i < enemy.size(); i++) {
            window->draw(enemy[i].getEnemy());
        }
        drawBomb(window);
        window->display();
    }
    //wyjscie z petli, tutaj trzeba zrobic ladnie
    if (player1.getDeath() == 1) {
        sf::Clock clockDeath;
        int i = 0;
        int j = 0;
        int lX = 0;
        int pX = 31;
        int dY = 21;
        int gY = 0;
        int actDir = 4; 
        while (i<651) {
            if (clockDeath.getElapsedTime().asSeconds() > 0.005) {
                switch (actDir)
                {
                case 4:
                    if (j == pX || j < 0) {
                        gY++; j = gY; actDir = 2;
                        break;
                    }
                    //cout << "4: " << gY * 31 + j << endl;
                    tile.getLevel()[gY * 31 + j] = 1;
                    j++;
                    i++;
                    break;
                case 2:
                    if (j == dY || j < 0) {
                        pX--; j = pX; actDir = 3;
                        break;
                    }
                   // cout << "2 " << pX + 31 * j - 1  << endl;
                    tile.getLevel()[pX + 31 * j - 1] = 1;
                    j++;
                    i++;
                    break;
                case 3:
                    if (j == lX || j < 0) {
                        dY--; j = dY; actDir = 1;
                        break;//dY * 31 - (31-j+1)
                    }
                    //cout << "3 "<< dY * 31 - (31 - j + 1) <<endl;
                    tile.getLevel()[dY * 31 - (31 - j + 1)] = 1;
                    j--;
                    i++;
                    break;
                case 1:
                    if (j == gY || j < 0) {
                        lX++; j = lX; actDir = 4;
                        break;
                    }
                    //cout << "4 "<< (j-1) * 31 + lX << endl;
                    tile.getLevel()[(j-1) * 31 + lX] = 1;
                    j--;
                    i++;
                    break;
                }
                tile.actu();
                window->clear();
                window->draw(tile);
                window->display();
                clockDeath.restart();
            }
        }
    }
    drawScoreAndExit(window);
    //informacja o zdobytym score
}
void Map::clockFps(sf::RenderWindow *window)
{
    checkChanges();//tymczasowo, plus totalnie bezsensowna duza ilosc wywolan na sprawdzenie, przydaloby sie pozniej samo rysowanie
    string1 = to_string((int)round(1.0 / clock.restart().asSeconds()));
    fps.setString(string1);
    window->draw(fps);
    string scoreS = score[1].getText().getString();
    if (std::stoi(scoreS) != scoreNumber) {
        score[1].setNewString(std::to_string(scoreNumber));
    }
}
void Map::createMap() {
    int level[] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    };//425zer
    //pokrycie ma byc zmienione zgodnie z poziomem trudnosci.
    srand(std::time(NULL));//od gracza 2 w lewo i 2 w dol nie moga byc 
    int pokrycie = 0;
    cout <<"PPP"<< (gameParam->getPokrycie() / 100 * 651) << endl;
    while (pokrycie < ((float)gameParam->getPokrycie()/100 * 420)/*220*/) {//420 maks
        int randomN = (std::rand() % 620) + 30;
       // cout << randomN << endl;
        if (randomN == 32 || randomN == 33 || randomN == 34 || randomN == 63 || randomN == 94 || level[randomN] == 1 || level[randomN] == 2) {
            continue;
        }
        level[randomN] = 2;
        pokrycie++;
    }
    int x = 31;
    int y = 21;
    tile.load("Map/map_til2.png", sf::Vector2u(32, 32), level, x, y);
    //enemy
    for (int i = 0; i <gameParam->getEnemyNumber(); i++) {
        enemy.push_back(Enemy());
        enemy[i].createEnemy(gameParam->getDif(), tile.getLevel(), &enemyTexture);
    }
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 31; j++) {
            if (tile.getLevel()[j + i * 31] == 9) {
                tile.getLevel()[j + i * 31] = 0;
            }
            cout << tile.getLevel()[j + i * 31] << " ";
            if (j == 30 && j != 0) { cout << endl; }
        }
    }
    tile.actu();
}
void Map::drawBomb(sf::RenderWindow* window)
{
    for (int i = 0; i < bomb.size(); i++) {
        //cout << "DRAWING " << bomb[i]->getSprite().getPosition().y << endl;
        if (bomb[i]->getState() == 0) {
            window->draw(bomb[i]->getSprite());
        }
        else {
            //drawing wokol.
            bomb[i]->drawFire(window, tile.getLevel());
            checkSomeoneLostLife(i);
            //sprawdzenie, czy ktos jest w zasiegu rysowanego 
        }
    }
}
void Map::drawBox(sf::RenderWindow*window)
{
    for (int i = 0; i < box.size(); i++) {
         window->draw(box[i].getBox());
    }
}
void Map::drawTopPanel(sf::RenderWindow* window)
{
    for (int i = 0; i < boosty.size(); i++) {
       boosty[i].setRestTime(&timeBoostPanel[i]);
    }
    for (int i = 0; i < boostPanel.size(); i++) {
        window->draw(boostPanel[i].getSprite());
    }
    for (int i = 0; i < timeBoostPanel.size(); i++) {
       window->draw(timeBoostPanel[i].getText());
    }
    window->draw(lifeText.getText());
    for (int i = 0; i < player1.getLife(); i++) {
        window->draw(life[i].getSprite());
    }
    for (int i = 0; i < score.size(); i++) {
        window->draw(score[i].getText());
    }
}
void Map::createTopPanel()
{
    boostPanel.push_back(DynamicTexture());
    boostPanel[0].setNew(&textureBoost, 160,0);
    boostPanel[0].editRectangle(0, 0, 32, 32);

    boostPanel.push_back(DynamicTexture());
    boostPanel[1].setNew(&textureBoost, 160, 32);
    boostPanel[1].editRectangle(32, 0, 32, 32);

    boostPanel.push_back(DynamicTexture());
    boostPanel[2].setNew(&textureBoost, 256, 0);
    boostPanel[2].editRectangle(64, 0, 32, 32);

    boostPanel.push_back(DynamicTexture());
    boostPanel[3].setNew(&textureBoost, 256, 32);
    boostPanel[3].editRectangle(96, 0, 32, 32);

    timeBoostPanel.push_back(StaticText());
    timeBoostPanel[0].setParametr(&font, sf::Color::White, "0", sf::Vector2u(202, 6), sf::Vector2u(0, 0), 20);
    
    timeBoostPanel.push_back(StaticText());
    timeBoostPanel[1].setParametr(&font, sf::Color::White, "0", sf::Vector2u(202, 38), sf::Vector2u(0, 0), 20);

    timeBoostPanel.push_back(StaticText());
    timeBoostPanel[2].setParametr(&font, sf::Color::White, "0", sf::Vector2u(298, 6), sf::Vector2u(0, 0), 20);

    timeBoostPanel.push_back(StaticText());
    timeBoostPanel[3].setParametr(&font, sf::Color::White, "0", sf::Vector2u(298, 38), sf::Vector2u(0, 0), 20);

    lifeText.setParametr(&font, sf::Color::White,"Lifes", sf::Vector2u(352, 6), sf::Vector2u(0, 0), 20);

    for (int i = 0; i < gameParam->getLife(); i++) {
        life.push_back(DynamicTexture());
        life[i].setNew(&lifeTexture, 352 + i * 32, 32);
    }

    boosty.push_back(ActiveBoost());
    boosty.push_back(ActiveBoost());
    boosty.push_back(ActiveBoost());
    boosty.push_back(ActiveBoost());
    
    score.push_back(StaticText());
    score.push_back(StaticText());
    score[0].setParametr(&font, sf::Color::White, "Score: ", sf::Vector2u(512,0), sf::Vector2u(0, 0), 26);
    score[1].setParametr(&font, sf::Color::White, "0", sf::Vector2u(512, 35), sf::Vector2u(0, 0), 26);

    score.push_back(StaticText());
    score[2].setParametr(&font, sf::Color::White, "Poziom: 1", sf::Vector2u(768, 0), sf::Vector2u(0, 0), 26);

    score.push_back(StaticText());
    cout <<"DIFFFIIS"<< gameParam->getDif() << endl;
    score[3].setParametr(&font, sf::Color::White, gameParam->getDif() == 2? "Trudny" : gameParam->getDif() == 1? "Sredni":"Latwy", sf::Vector2u(768, 35), sf::Vector2u(0, 0), 20);
}
void Map::checkSomeoneLostLife(int i)
{
    if (player1.getTemporaryInvincible() == 0 && boosty[2].getStatus() == 0 && bomb[i]->killPlayer(player1.getPositionX(), player1.getPositionY(), player1.getFrame(), player1.getDir(), 8) == 1) {
        player1.setLife(player1.getLife() - 1);
        player1.setTemporaryInvincible(1);
        if (player1.getLife() == 0) {
            gameEnd();
            cout << "KONIEC GRY" << endl;
        }
    }
    for (int j = 0; j < enemy.size(); j++) {
        //cout << "enemy: " << endl;
        if (bomb[i]->killPlayer(enemy[j].getX() - 1, enemy[j].getY() - 1, enemy[j].getFrame(), enemy[j].getDir(), 16) == 1) {
            cout << "Enemys dead: " << j <<endl;
            scoreNumber += gameParam->getScorePerEnemy();
            for (int i = 0; i < 21; i++) {
                for (int j = 0; j < 31; j++) {
                    cout << tile.getLevel()[j + i * 31] << " ";
                    if (j == 30 && j != 0) { cout << endl; }
                }
            }
            cout << endl;
            tile.getLevel()[enemy[j].getX() + enemy[j].getY() * 31] = 0;
            for (int i = 0; i < 21; i++) {
                for (int j = 0; j < 31; j++) {
                    cout << tile.getLevel()[j + i * 31] << " ";
                    if (j == 30 && j != 0) { cout << endl; }
                }
            }
            enemy.erase(enemy.begin() + j);
            if (enemy.size() == 0) {
                cout << "BREAKS<" << endl;
                gameParam->difActuAfterComplete(gameParam->getDif());
                bomb.clear();
                box.clear();
                player1.restart();
                createMap();
                score[2].setNewString("Poziom " + std::to_string(gameParam->getLevel()));
                loading = 1;
                break;
            }
        }
    }
}
void Map::gameEnd()
{
    player1.setDeath(1);
    breakGame = 1;
}
void Map::pauseF(sf::RenderWindow * window)
{
    sf::RectangleShape filter(sf::Vector2f(31*32, 23*32));
    filter.setFillColor(sf::Color(0, 0, 0, 5));
    sf::Text pauseText("PAUSED", font, 25);
    sf::Text infoText("Wcisnij dowolny klawisz, aby kontynowac. [escape - wyjscie]", font, 20);
    //pauseText.setColor(sf::Color(247, 148, 142));
    pauseText.setPosition((31 * 32) / 2 - pauseText.getGlobalBounds().width / 2, (32*23) / 2);
    infoText.setPosition((31 * 32) / 2 - infoText.getGlobalBounds().width / 2, (32 * 25) / 2);
    sf::Event event;
    while (pause == 1) {
        window->draw(filter);
        window->draw(pauseText);
        window->draw(infoText);
        window->display();
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed && event.key.code != sf::Keyboard::Escape) {
                pause = 0;
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                pause = 0;
                breakGame = 1;
            }
        }
    }
}
void Map::drawScoreAndExit(sf::RenderWindow* window)
{
    sf::RectangleShape filter(sf::Vector2f(31 * 32, 23 * 32));
    filter.setFillColor(sf::Color(0, 0, 0, 5));
    sf::Text scoreText("Your score:", font, 25);
    sf::Text scoreEnd(std::to_string(scoreNumber), font, 25);
    sf::Text infoText("Wcisnij dowolny klawisz, aby kontynowac.", font, 20);
    //pauseText.setColor(sf::Color(247, 148, 142));
    scoreText.setPosition((31 * 32) / 2 - scoreText.getGlobalBounds().width / 2, (32 * 20) / 2);
    scoreEnd.setPosition((31 * 32) / 2 - scoreEnd.getGlobalBounds().width / 2, (32 * 22) / 2);
    infoText.setPosition((31 * 32) / 2 - infoText.getGlobalBounds().width / 2, (32 * 40) / 2);
    sf::Event event;
    int ret = 0;
    while (ret == 0) {
        window->clear();
        window->draw(filter);
        window->draw(scoreText);
        window->draw(scoreEnd);
        window->draw(infoText);
        window->display();
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                ret = 1;
            }
        }
    }
}
void Map::checkUnder()
{
    for (int i = 0; i < box.size(); i++) {
        //cout << box[i].getX() << " " << player1.getPositionX() << " " << box[i].getY() << " " << player1.getPositionY() << endl;
        if (box[i].getX() == player1.getPositionX() && box[i].getY() == player1.getPositionY()) {
            cout << "MAMY TO!" << endl;
            boosty[box[i].getBoostType()].AddTime(10.f, &timeBoostPanel[box[i].getBoostType()]);
            box.erase(box.begin() + i);
            break;
        }
    }
}
void Map::checkChanges()
{
    if (clockEnemy.getElapsedTime().asSeconds() > gameParam->getEnemySpeed()) {
        for (int i = 0; i < enemy.size(); i++) {
            enemy[i].move(tile.getLevel(), player1.getPositionX() +1, player1.getPositionY() + 1, box, gameParam->getChanceToChangeDir(), bomb, gameParam->getBombRange());
            if (player1.getTemporaryInvincible() == 0 && enemy[i].killPlayer(player1.getPositionX(), player1.getPositionY(), player1.getDir(), player1.getFrame(), 8) == 1) {
                player1.setLife(player1.getLife() - 1);
                player1.setTemporaryInvincible(1);
                if (player1.getLife() == 0) {
                    gameEnd();
                    cout << "KONIEC GRY" << endl;
                }
            }
        }
        clockEnemy.restart();
        tile.actu();
    }
    if (bomb.size() > 0) {
        for (int i = 0; i < bomb.size(); i++) {
            if (bomb[i]->timeToExplode() == 1) {
                cout << "EXPLODE" << endl;
                /*for (int i = 0; i < 21; i++) {
                    for (int j = 0; j < 31; j++) {
                        cout << tile.getLevel()[j + i * 31] << " ";
                        if (j == 30 && j != 0) { cout << endl; }
                    }
                }*/
                bomb[i]->explode(tile.getLevel(), box, gameParam->getChanceToBoost(), &textureBoost, &scoreNumber, gameParam->getScorePerWall());
                //checkSomeoneLostLife(i);
                //sprwdzenie, czy w zasiegu bomby jest przeciwnik,gracz;
                tile.actu();
               /* for (int i = 0; i < 21; i++) {
                    for (int j = 0; j < 31; j++) {
                        cout << tile.getLevel()[j + i * 31] << " ";
                        if (j == 30 && j != 0) { cout << endl; }
                    }
                }*/
                cout << endl << endl;
            }
            if (bomb[i]->getState() == 1 && bomb[i]->explodeEnd() == 1) {
                if (bomb.size() == 1) {
                    delete bomb[0];//dodane
                    bomb.clear();
                }
                else {
                    delete bomb[i];//dodane
                    bomb.erase(bomb.begin() + i);                    
                }
            }
        }
    }
} 
void Map::checkPlayerContinueMove(sf::RenderWindow* window)
{
   // cout << "SPEED: " << (boosty[1].getStatus() == 1 ? 1.f / 25 : speed) << endl;
    if (clockMove.getElapsedTime().asSeconds() > (boosty[1].getStatus() == 1 ? 1.f / 25 : gameParam->getPlayerSpeed())) {//do przeniesienia ruch gracza
        if ((player1.getMove() == 1 && player1.getFrame() == 0) || player1.getFrame() != 0 || (player1.getDirectionChange() == 1 && lastKey == nextKey)) {
           // cout << "DUPA" << endl;
            if (player1.checkCollision(tile.getLevel(), bomb, boosty[3].getStatus()) == 1) {
                bombChecked = 0;
                player1.move(window, tile.getLevel());
                clockMove.restart();
            }
            else {
                player1.stop();
            }
        }
        else if (player1.getDirectionChange() == 1 && player1.getFrame() == 0) {
           // cout << "DUPA1" << endl;
            player1.changeDirection(nextKey);
            player1.setDirectionChange(0);
            player1.setMove(1);
            lastKey = nextKey;
            if (player1.checkCollision(tile.getLevel(), bomb, boosty[3].getStatus()) == 1) {
                bombChecked = 0;
                player1.move(window, tile.getLevel());
            }
            else {
                player1.stop();
            }
        }
    }
    if(player1.getMove() == 0 && player1.getFrame() == 0 && player1.getSprite().getTextureRect().left !=0){
        player1.stop();
    }
    if (bombChecked == 0) {
        //cout << "SPRAWDZAM" << endl;
        checkUnder();
        bombChecked = 1;
    }
}
void Map::events(sf::RenderWindow* window)
{
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
        {
            if (event.type == event.KeyPressed && (player1.getMove() == 1 || player1.getFrame() != 0)) {//
                nextKey = event.key.code;
                player1.setMove(0);
                player1.setDirectionChange(1);
                cout << "NEXTKEY" << endl;
            }
            if (event.type == event.KeyReleased && event.key.code == nextKey) {
                cout << "KEYRELASEDNEXT" << endl;
                player1.setDirectionChange(0);
                sf::Keyboard::isKeyPressed(lastKey) ? player1.setMove(1) : player1.setMove(0);
            }
            if (event.type == event.KeyReleased && event.key.code == lastKey) {
                cout << "KEYRELASED" << endl;
                player1.setMove(0);
            }
            if (event.type == event.KeyPressed && player1.getMove() == 0 && player1.getFrame() == 0) {
                cout << "KEYPRESSED" << endl;
                player1.setMove(1);
                lastKey = event.key.code;
                player1.changeDirection(event.key.code);
            }
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && /*player1.getMove() == 0 &&*/ player1.getFrame() == 0 && tile.getLevel()[player1.getPositionX() + 1 + (player1.getPositionY() + 1) * 31] !=2) {
                if (bomb.size() < player1.getBombLimit() + (boosty[0].getStatus() == 1 ? 1 : 0)) {
                    for (int i = 0; i < bomb.size(); i++) {//sprawdzenie czy bomba nie lezy w tym miejscu
                        if (bomb[i]->getPositionX() == player1.getPositionX() && bomb[i]->getPositionY() == player1.getPositionY()) {
                            return;
                        }
                    }
                    bomb.push_back(new Bomb(player1.getSprite().getPosition().x -32, player1.getSprite().getPosition().y - 96, gameParam->getBombRange()));//x, y, range
                }
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
            pause = 1;
        }
    }
}