#ifndef MOTIM_H
#define MOTIM_H

#include "Eventos.h"


class Motim : public Eventos
{
public:
	Motim(Mundo *mundo) : Eventos(mundo, TTL_MOTIM) {};
	~Motim();
};
#endif // !MOTIM_H
