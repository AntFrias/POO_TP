#include "Terra.h"


Terra::Terra(int x, int y, char t)
{
	this->t = t;
	this->x = x;
	this->y = y;
}

const char Terra::getChar()const{
	return this->t;
}

const int Terra::getX()const{
	return this->x;
}

const int Terra::getY()const{

	return this->y;
}
Terra & Terra::getTerra(){
	return *this;
}

Terra::~Terra()
{
}
