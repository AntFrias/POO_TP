#ifndef ESCUNA_H
#define ESCUNA_H

#include "Navios.h"

class Escuna : public Navios
{
	int QuantMercadoria;
	int QuantPeixe;

public:
	Escuna(Mundo *mundo, int coordx, int coordy) : QuantMercadoria(0), QuantPeixe(0), Navios(mundo, 'E', coordx, coordy, 10, 100) {};
	virtual void AbasteceAguaNavio();
	bool VerificaCargaNavio(int novaCarga);
	~Escuna();
};

#endif // !ESCUNA_H