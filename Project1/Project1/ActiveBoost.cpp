#include "ActiveBoost.h"

int ActiveBoost::getStatus()
{
	return status;
}

void ActiveBoost::AddTime(float time, StaticText *text)
{
	if (status == 0) {
		timeToEnd = 10;
		timeStart.restart();
		status = 1;
	}
	else if (status == 1) {
		timeToEnd += 10;
	}
	setRestTime(text);
}

void ActiveBoost::setRestTime(StaticText* text)
{
	if (timeToEnd - timeStart.getElapsedTime().asSeconds() < 0 && status != 0) {
		text->setNewString("0");
		status = 0;
	}
	else if(status == 1){
		std::string newString;
		newString = std::to_string((int)timeToEnd - (int)timeStart.getElapsedTime().asSeconds());
		text->setNewString(newString);
	}
}
