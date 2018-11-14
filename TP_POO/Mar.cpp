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

char Mar::getTipo()
{
	return this->t;
}


Mar::~Mar()
{
}
