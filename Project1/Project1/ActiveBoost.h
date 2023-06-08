#pragma once
#include "StaticText.h"
#include <iostream>
class ActiveBoost
{
public:
	int getStatus();
	void AddTime(float, StaticText*);
	void setRestTime(StaticText*);
private:
	sf::Clock timeStart;
	float timeToEnd;
	int status = 0;
};

