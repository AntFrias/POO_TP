#include "Terra.h"


Terra::Terra(int x, int y, char t)
{
	this->t = t;
	this->x = x;
	this->y = y;
}

char Terra::getT()
{
	return this->t;
}

int Terra::getX()
{
	return this->x;
}

int Terra::getY() {

	return this->y;
}

Terra::~Terra()
{
}
