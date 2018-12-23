#include "Motim.h"
#include "Mundo.h"




int Motim::getTTL() const {

	return this->TTL;

}
void Motim::setTTL()
{
	this->TTL = TTL_MOTIM;
}
string Motim::TrataEvento()
{
	ostringstream os;

	if (this->TTL == 0)
		os << mundo->TrataEventoMotim(MOTIM_ESTADO_FIM_MOTIM);
	
	if (this->TTL == TTL_MOTIM)
		os << mundo->TrataEventoMotim(MOTIM_ESTADO_INICIO_MOTIM);
	
	this->TTL = this->TTL - 1;

	os << "Duracao do Motim " << this->TTL << endl;
	
	return os.str();
}


Motim::~Motim()
{
}
