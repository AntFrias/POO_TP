#include "Superficie.h"


/*
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Classe Base Superficie 
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/

Superficie::Superficie(const Superficie &aux) {

	this->x = aux.x;
	this->y = aux.y;

}

Superficie::Superficie()
{
}

//Superficie * Superficie::Duplica() const
//{
//	return new Superficie(*this);
//}

int Superficie::getX()const { return this->x; };
int Superficie::getY()const { return this->y; };

Superficie::~Superficie()
{
}


