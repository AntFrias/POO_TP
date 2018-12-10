#ifndef GALEAO_H
#define GALEAO_H

#include "Navios.h"

class Galeao : public Navios
{
	int QuantMercadoria;
	int QuantPeixe;

public:
	Galeao(Mundo *mundo, int coordx, int coordy, int numSoldados = 70) : QuantMercadoria(0), QuantPeixe(0), Navios(mundo, 'G', coordx, coordy, numSoldados, 400){};
	~Galeao();
};
#endif // !GALEAO_H
