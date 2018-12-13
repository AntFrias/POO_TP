#include "Porto.h"

Porto::Porto(int x, int y, char tipoPorto)
{
	this->TipoPorto = tipoPorto;
	this->x = x;
	this->y = y;
	
}
bool Porto::verificaPortoAmigo() {

	if ((this->TipoPorto >= 'A' && this->TipoPorto <= 'Z'))
		return true;
	else
	return false;	
}
const int Porto::getX() const {

	return this->x;
}
const int Porto::getY() const {

	return this->y;
}
void Porto::setX(int x)  {

	this->x = x;
}
void Porto::setY(int y) {

	this->y = y;
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
