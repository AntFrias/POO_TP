#ifndef CALMARIA_H
#define CALMARIA_H

#include "Eventos.h"

#define EVENTO_CALMARIA 3

class Calmaria : public Eventos
{
public:
	Calmaria(Mundo *mundo) : Eventos(mundo, EVENTO_CALMARIA) {};
	virtual bool ValidaEventoCalmaria();
	virtual void TrataEventoCalmaria();
	virtual void TrataEventoMotim() {};
	~Calmaria();
};
#endif // !CALMARIA_H
