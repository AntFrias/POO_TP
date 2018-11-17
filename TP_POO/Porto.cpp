#include "Porto.h"

Porto::Porto(int x, int y, char t)
{
	this->t = t;
	this->x = x;
	this->y = y;
}

const int Porto::getX() const {

	return this->x;
}
const int Porto::getY() const {

	return this->y;
}
const char Porto::getChar() const {

	return this->t;
}
Porto & Porto::getPorto()
{
	return *this;
}


Porto::~Porto()
{
}
