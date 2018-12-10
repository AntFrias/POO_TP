#include "Porto.h"

Porto::Porto(int x, int y, char tipoPorto)
{
	this->TipoPorto = tipoPorto;
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

	return this->TipoPorto;
}
Porto & Porto::getPorto()
{
	return *this;
}


Porto::~Porto()
{
}
