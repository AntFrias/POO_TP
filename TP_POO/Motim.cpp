#include "Motim.h"
#include "Mundo.h"




int Motim::getTTL() const {

	return this->TTL;

}
void Motim::setTTL()
{
	this->TTL = TTL_MOTIM;
}
string Motim::TrataEvento(int modoExecucao, int idNavio, int coordX, int coordY)
{
	
	ostringstream os;

		if (this->TTL == TTL_MOTIM){
			os << mundo->TrataEventoMotim(MOTIM_ESTADO_INICIO_MOTIM, modoExecucao, idNavio);
		}
		this->TTL = this->TTL - 1;
		if (this->TTL == 0) {
			os << mundo->TrataEventoMotim(MOTIM_ESTADO_FIM_MOTIM, modoExecucao, idNavio);	
		}		
	
		
		// esta verificaçao tem de ser aqui porque o metodo que chama este é que determina o estado do evento
		os << "Duracao do Motim " << this->TTL << endl;
	return os.str();
}


Motim::~Motim()
{
}
