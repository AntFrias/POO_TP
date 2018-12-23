#include "Calmaria.h"
#include "Mundo.h"


string Calmaria::TrataEvento()
{
	ostringstream os;

	static int epicentroX, epicentroY;

	int dimX = mundo->getDimX(), dimY = mundo->getDimY();

	if (this->TTL == TTL_CALMARIA) {

		epicentroX = rand() % ((mundo->getDimX() - 2) - 2) + 2;

		epicentroY = rand() % ((mundo->getDimY() - 2) - 2) + 2;

		os << " Vai ser criada uma Calmaria" << endl;

	}
	os << " Gerou-se uma calmaria nas coordenadas: " << epicentroX << " , " << epicentroY << endl;

	os << mundo->TrataEventoCalmaria(epicentroX, epicentroY);

	os << "Duracao da Calmaria : " << this->TTL << endl;
		
	this->TTL = this->TTL - 1;

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
