#include "Calmaria.h"
#include "Mundo.h"


string Calmaria::TrataEvento()
{
	ostringstream os;

	static int epicentroX, epicentroY;

	int dimX = mundo->getDimX(), dimY = mundo->getDimY();

	if (this->TTL == TTL_CALMARIA) {

		do {

			epicentroX = rand() % dimX + 1;

			epicentroY = rand() % dimY + 1;

		} while (epicentroX >= 0 + 2 && epicentroX < dimX - 3 && epicentroY >= 0 + 2 && epicentroY <= dimY - 3);

		os << "Vai ser gerada uma calmaria nas coordenadas: " << epicentroX << ", " << epicentroY << endl;

	}

		mundo->TrataEventoCalmaria(epicentroX, epicentroY);

		this->TTL = this->TTL - 1;

		os << "Duracao da Calmaria : " << this->TTL << endl;

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
