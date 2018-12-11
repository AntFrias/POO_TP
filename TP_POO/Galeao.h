#ifndef GALEAO_H
#define GALEAO_H

#include "Navios.h"

class Galeao : public Navios
{
	int QuantMercadoria;
	int QuantPeixe;

public:
	Galeao(Mundo *mundo, int coordx, int coordy) : QuantMercadoria(0), QuantPeixe(0), Navios(mundo, 'G', coordx, coordy, 40, 400){};
	virtual void AbasteceAguaNavio();
	bool VerificaCargaNavio(int novaCarga);
	~Galeao();
};
#endif // !GALEAO_H
