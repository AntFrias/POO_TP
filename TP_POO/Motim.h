#ifndef MOTIM_H
#define MOTIM_H

#include "Eventos.h"

#define EVENTO_MOTIM 4

using namespace std;

class Motim : public Eventos
{
public:
	Motim(Mundo *mundo) : Eventos(mundo, EVENTO_MOTIM) {};
	virtual string TrataEvento();
	virtual bool VerificaEventoCalmaria() { return false; };
	virtual int getTTL() const;
	virtual void setTTL();
	
	~Motim();
};
#endif // !MOTIM_H
