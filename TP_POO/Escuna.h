#ifndef ESCUNA_H
#define ESCUNA_H

#include "Navios.h"

class Escuna : public Navios
{
	int QuantMercadoria;
	int QuantPeixe;

public:
	Escuna(Mundo *mundo, int coordx, int coordy, int numSoldados = 20) : QuantMercadoria(0), QuantPeixe(0), Navios(mundo, 'E', coordx, coordy, numSoldados, 100) {};
	~Escuna();
};

#endif // !ESCUNA_H