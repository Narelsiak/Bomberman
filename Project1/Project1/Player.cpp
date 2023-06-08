#include "Player.h"

void Player::init()
{
    dir = 0;
    klatka = 0;
    loadSprite();
}

void Player::changeCord()
{
    switch (dir) {
    case 1:
        y--;
        break;
    case 2:
        y++;
        break;
    case 3:
        x--;
        break;
    case 4:
        x++;
        break;
    }
}

void Player::loadSprite()
{
   if (!texturePlayer.loadFromFile("Menu/playerGraph.gif"))
    {
        // error...
    }
    player.setTexture(texturePlayer);
    player.setPosition(sf::Vector2f(32.f, 96.f)); // absolute position
    player.setTextureRect(sf::IntRect(0, 64, 32, 32));

    player1.setnew("Menu/playerGraph.gif", 0.f, 32.f);
    player1.editRectangle(0, 64, 32, 32);
}

void Player::editPosition(sf::RenderWindow* window, sf::Keyboard::Key key)
{
        switch (key) {
        case sf::Keyboard::Key::Up:
            if (player.getTextureRect().left <= 191) {
                player.setTextureRect(sf::IntRect(player.getTextureRect().left + 32, 0, 32, 32));
            }
            else {
                player.setTextureRect(sf::IntRect(32, 0, 32, 32));
            }
            break;
        case sf::Keyboard::Key::Down:
            if (player.getTextureRect().left <= 191) {
                player.setTextureRect(sf::IntRect(player.getTextureRect().left + 32, 64, 32, 32));
            }
            else {
                player.setTextureRect(sf::IntRect(32, 64, 32, 32));
            }
            break;
        case sf::Keyboard::Key::Left:
            if (player.getTextureRect().left <= 191) {
                player.setTextureRect(sf::IntRect(player.getTextureRect().left + 32, 96, 32, 32));
            }
            else {
                player.setTextureRect(sf::IntRect(32, 96, 32, 32));
            }
            break;
        case sf::Keyboard::Key::Right:
            if (player.getTextureRect().left <= 191) {
                player.setTextureRect(sf::IntRect(player.getTextureRect().left + 32, 32, 32, 32));
            }
            else {
                player.setTextureRect(sf::IntRect(32, 32, 32, 32));
            }
            break;
    }
}

int Player::checkAllIsBlocked(int* map, int posX, int posY)
{
    posX += 1;
    posY += 1;
    if(map[posX + posY * 31] == 2 && map[posX + (posY-1) * 31] != 0 && map[posX + (posY+1) * 31] != 0 && map[posX - 1 + posY * 31] != 0 && map[posX + 1 + posY * 31] != 0) {
        return 1;
    }
    return 0;
}

void Player::move(sf::RenderWindow* window, int* map)
{
    // cout << klatka << endl;
    float times = 1;
    float time_in_seconds = times / 7;
    float move_speed = 4;
    sf::Vector2f pos = player.getPosition();
    switch (dir) {
    case 1:
        editPosition(window, sf::Keyboard::Up);
        player.setPosition(pos.x, pos.y - (move_speed));
        break;
    case 2:
        editPosition(window, sf::Keyboard::Down);
        player.setPosition(pos.x, pos.y + (move_speed));
        break;
    case 3:
        editPosition(window, sf::Keyboard::Left);
        player.setPosition(pos.x - (move_speed), pos.y);
        break;
    case 4:
        editPosition(window, sf::Keyboard::Right);
        player.setPosition(pos.x + (move_speed), pos.y);
        break;
    }

    //sumaryczna przebyta odleglosc musi byc TAKA SAMA
    klatka++;
    //std::cout << klatka << std::endl;
    if (klatka == 8) {
        klatka = 0;
        changeCord();
        std::cout << "Player x: " << x << std::endl << "Player y: " << y << std::endl;
    }
}

void Player::stop()
{
    if ((klatka == 0 && czyMove == 0 && player.getTextureRect().left !=0) || (czyMove == 1 && player.getTextureRect().left == 0)) {
        switch (dir) {
        case 1:
            player.setTextureRect(sf::IntRect(0, 0, 32, 32));
            break;
        case 2:
            player.setTextureRect(sf::IntRect(0, 64, 32, 32));
            break;
        case 3:
            player.setTextureRect(sf::IntRect(0, 96, 32, 32));
            break;
        case 4:
            player.setTextureRect(sf::IntRect(0, 32, 32, 32));
            break;
        }
    }    
}

void Player::restart()
{
    klatka = 0;
    czyMove = 0;
    changeDir = 0;
    x = 0;
    y = 0;
    player.setPosition(sf::Vector2f(32.f, 96.f)); // absolute position
    player.setTextureRect(sf::IntRect(0, 64, 32, 32));
}

sf::Sprite Player::getSprite()
{
    return player;
    return player1.getSprite();
}

void Player::setLife(int life)
{
    lifes = life;
}

int Player::getLife()
{
    return lifes;
}

void Player::changeDirection(sf::Keyboard::Key key)
{
    switch (key) {
    case sf::Keyboard::Up:
        dir = 1;
        break;
    case sf::Keyboard::Down:
        dir = 2;
        break;
    case sf::Keyboard::Left:
        dir = 3;
        break;
    case sf::Keyboard::Right:
        dir = 4;
        break;
    }
}

int Player::getMove()
{
    return czyMove;
}

int Player::getFrame()
{
    return klatka;
}

int Player::getDirectionChange()
{
    return changeDir;
}

void Player::setMove(int move)
{
    czyMove = move;
}

void Player::setStopStatus(int s)
{
    stopStatus = s;
}

int Player::getStopStatus()
{
    return stopStatus;
}

void Player::setFrame(int frame)
{
    klatka = frame;
}

void Player::setDirectionChange(int dir)
{
    changeDir = dir;
}

int Player::getBombLimit()
{
    return bombLimit;
}

void Player::setBombLimit(int e)
{
    bombLimit = e;
}

int Player::getPositionX()
{
    return x;
}

int Player::getPositionY()
{
    return y;
}

int Player::checkCollision(int* map, std::vector <Bomb*> bomb, int wallStatus)
{
    switch (dir) {
    case 1:
        if (map[x + 1 + (y) * 31] == 0 || (map[x + 1 + (y) * 31] == 2 && wallStatus == 1) || (map[x + 1 + (y) * 31] == 2 && checkAllIsBlocked(map, x, y) == 1)){
            for (int i = 0; i < bomb.size(); i++) {
                if (bomb[i]->getState() == 0 && x == bomb[i]->getPositionX() && y - 1 == bomb[i]->getPositionY()) {
                    return 0;
                }
            }
            return 1; 
        }
        break;
    case 2:
        if (map[x + 1 + (y + 2) * 31] == 0 || (map[x + 1 + (y + 2) * 31] == 2 && wallStatus == 1) || (map[x + 1 + (y + 2) * 31] == 2 && checkAllIsBlocked(map, x, y) == 1)) {
            for (int i = 0; i < bomb.size(); i++) {
                if (bomb[i]->getState() == 0 && x == bomb[i]->getPositionX() && y + 1 == bomb[i]->getPositionY()) {
                    return 0;
                }
            }
            return 1; 
        }
        break;
    case 3:
        if (map[x + (y + 1) * 31] == 0 || (map[x + (y + 1) * 31] == 2 && wallStatus == 1) || (map[x + (y + 1) * 31] == 2 && checkAllIsBlocked(map, x, y) == 1)) {
            for (int i = 0; i < bomb.size(); i++) {
                if (bomb[i]->getState() == 0 && x-1 == bomb[i]->getPositionX() && y == bomb[i]->getPositionY()) {
                    return 0;
                }
            }
            return 1; 
        }
        break;
    case 4: 
        if (map[x + 2 + (y + 1) * 31] == 0 || (map[x + 2 + (y + 1) * 31] == 2 && wallStatus == 1) || (map[x + 2 + (y + 1) * 31] == 2 && checkAllIsBlocked(map, x, y) == 1)) {
            for (int i = 0; i < bomb.size(); i++) {
                if (bomb[i]->getState() == 0 && x + 1 == bomb[i]->getPositionX() && y == bomb[i]->getPositionY()) {
                    return 0;
                }
            }
            return 1; 
        }
        break;
    }
    return 0;
}

int Player::getTemporaryInvincible()
{
    return temporaryInvincible;
}

void Player::setTemporaryInvincible(int i)
{
    temporaryInvincible = i;
    if (i == 1) {
        invincibleClock.restart();
        frameInvi = 0;
    }
}

int Player::checkInvincibleEnd()
{
    if (temporaryInvincible == 1) {
        if (invincibleClock.getElapsedTime().asSeconds() > 5) {
            temporaryInvincible = 0;
        }
        if (frameInvi == 5) {
            frameInvi = 0;
            return 0;
        }
        frameInvi++;
    }
    return 1;
}

int Player::getDir()
{
    return dir;
}

int Player::getDeath()
{
    return death;
}

void Player::setDeath(int d)
{
    death = d;
}
