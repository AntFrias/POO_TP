#ifndef TEMPESTADE_H
#define TEMPESTADE_H

#include "Eventos.h"

class Tempestade : public Eventos
{
public:
	Tempestade(Mundo *mundo) : Eventos(mundo, TTL_TEMPESTADE) {};
	~Tempestade();
};
#endif // !TEMPESTADE_H
