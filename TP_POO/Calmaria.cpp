#include "Calmaria.h"
#include "Mundo.h"


string Calmaria::TrataEvento(int modoExecucao, int idNavio, int coordX, int coordY, int duracao)
{
	ostringstream os;

	static int epicentroX, epicentroY;

	int dimX = mundo->getDimX(), dimY = mundo->getDimY();

	if (this->TTL == duracao) {

		if ( modoExecucao != EVENTO_EXECUCAO_COMANDO){

			epicentroX = rand() % ((mundo->getDimX() - 2) - 2) + 2;

			epicentroY = rand() % ((mundo->getDimY() - 2) - 2) + 2;
		
		}
		else {

			epicentroX = coordX;

			epicentroY = coordY;

		}
		
		os << " Vai ser criada uma Calmaria" << endl;

	}

	os << " Gerou-se uma calmaria nas coordenadas:  [ " << epicentroX << " : " << epicentroY << " ] " <<  endl;
	if (this->TTL > 0){
		os << mundo->TrataEventoCalmaria(epicentroX, epicentroY, CALMARIA_ESTADO_EM_EXECUCAO_CALMARIA);
		
		this->TTL = this->TTL - 1;
	}


	if (this->TTL == 0){
		os << mundo->TrataEventoCalmaria(epicentroX, epicentroY, CALMARIA_ESTADO_FIM_CALMARIA);
	
	}

	//os << endl <<endl << "Duracao da Calmaria : " << this->TTL << endl << endl;

	return os.str();
}

int Calmaria::getTTL() const
{
	return this->TTL;
}

void Calmaria::setTTL()
{
	this->TTL = EVENTO_CALMARIA;
}

Calmaria::~Calmaria()
{
}
