#ifndef FRAGATA_H
#define FRAGATA_H

#include "Navios.h"

class Fragata : public Navios
{

public:
	Fragata(Mundo *mundo, int coordx, int coordy) : Navios(mundo, 'F', coordx, coordy, 50, 500) {};
	virtual void AbasteceAguaNavio();
	bool souFragata();
	~Fragata();
};

#endif // !FRAGATA_H
