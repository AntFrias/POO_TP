#ifndef VELEIRO_H
#define VELEIRO_H

#include "Navios.h"


class Veleiro : public Navios
{
	int QuantMercadoria;
	int QuantPeixe;

public:
	Veleiro(Mundo *mundo, int coordx, int coordy, int numSoldados = 20) : QuantMercadoria(0), QuantPeixe(0), Navios(mundo, 'V', coordx,coordy, numSoldados, 200){};
	~Veleiro();
};
#endif // !VELEIRO_H
