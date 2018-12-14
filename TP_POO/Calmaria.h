#ifndef CALMARIA_H
#define CALMARIA_H

#include "Eventos.h"

class Calmaria : public Eventos
{
public:
	Calmaria(Mundo *mundo) : Eventos(mundo, TTL_CALMARIA) {};
	~Calmaria();
};
#endif // !CALMARIA_H
