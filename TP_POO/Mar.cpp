#include "Mar.h"



Mar::Mar()
{
}

Mar::Mar(int x,int y, char t)
{
	this->t = t;
	this->x = x;
	this->y = y;
}
int Mar::getX() {

	return this->x;
}
int Mar::getY() {

	return this->y;
}
Mar & Mar::getMar()
{
	return *this;
}



Mar::~Mar()
{
}
