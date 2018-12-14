#ifndef EVENTOS_H
#define EVENTOS_H

#include "Mundo.h"

#define TTL_TEMPESTADE 1
#define TTL_SEREIA 1
#define TTL_CALMARIA 3
#define TTL_MOTIM 4

class Eventos
{
	Mundo *mundo;

	int TTL;
	

public:
	Eventos(Mundo *mundo, int TTL);
	~Eventos();
};
#endif // !EVENTOS_H
