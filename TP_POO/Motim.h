#ifndef MOTIM_H
#define MOTIM_H

#include "Eventos.h"

#define EVENTO_MOTIM 4

class Motim : public Eventos
{
public:
	Motim(Mundo *mundo) : Eventos(mundo, EVENTO_MOTIM) {};
	virtual bool ValidaEventoCalmaria();
	int getTTL() const;
	void setTTL();
	virtual void TrataEvento();
	~Motim();
};
#endif // !MOTIM_H
