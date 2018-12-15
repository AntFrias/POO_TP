#ifndef MOTIM_H
#define MOTIM_H

#include "Eventos.h"

#define EVENTO_MOTIM 4

class Motim : public Eventos
{
public:
	Motim(Mundo *mundo) : Eventos(mundo, EVENTO_MOTIM) {};
	virtual bool ValidaEventoCalmaria();
	virtual void TrataEventoCalmaria() {};
	virtual void TrataEventoMotim();
	~Motim();
};
#endif // !MOTIM_H
