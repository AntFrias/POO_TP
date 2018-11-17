#include "Mar.h"


Mar::Mar(int x,int y, char t)
{
	this->t = t;
	this->x = x;
	this->y = y;
}
const int Mar::getX() const{

	return this->x;
}
const int Mar::getY() const{

	return this->y;
}
const char Mar::getChar() const {

	return this->t;
}
Mar & Mar::getMar()
{
	return *this;
}



Mar::~Mar()
{
}
