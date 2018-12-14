#ifndef SEREIA_H
#define SEREIA_H

#include "Eventos.h"

class Sereia : public Eventos
{
public:
	Sereia(Mundo *mundo) : Eventos(mundo, TTL_SEREIA) {};
	~Sereia();
};
#endif // !SEREIA_H
