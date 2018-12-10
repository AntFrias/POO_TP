#ifndef FRAGATA_H
#define FRAGATA_H

#include "Navios.h"

class Fragata : public Navios
{

public:
	Fragata(Mundo *mundo, int coordx, int coordy, int numSoldados = 50) : Navios(mundo, 'F', coordx, coordy, numSoldados, 500) {};
	~Fragata();
};

#endif // !FRAGATA_H
