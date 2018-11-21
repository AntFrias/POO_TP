#include "Mundo.h"
#include "Jogador.h"
using namespace std;
Mundo::Mundo() {

}
void Mundo::moveNavio(int id,int direcao) {

	signed int x, y;

	for (unsigned int i = 0; i < navios.size(); i++) {
		
		if (navios[i]->getId() == id) {

			switch (direcao) {

			case moveEsquerda:
				x = navios[i]->getX() - 1;
				//e ver se a nova pos está dentro de agua!
				if (x >= 0) {
					navios[i]->setX(navios[i]->getX() - 1);
				}
				break;
			default:
				break;
			}
		}
	}
}
Navios & Mundo::criaNavio(const char tipo) {

	int x, y;
	Navios *aux;
	for (unsigned int i = 0; i < porto.size(); i++) {

		if (porto[i]->getChar() == tipo) {

			x = porto[i]->getX();

			y = porto[i]->getY();
		}
	}
	aux = new Navios(tipo, x, y);
	
	this->navios.push_back(aux);

	return *aux;
}
const char Mundo::getPortoPrincipal() {

	for (unsigned int i = 0; i < porto.size(); i++) {

		if (porto[i]->getChar() >= 'A' && porto[i]->getChar() <= 'Z') {

			return porto[i]->getChar();

		}	
	}
	return '-';

}
void Mundo::criaCelulaMar(int x, int y)
{

	this->mar.push_back(new Mar(x,y));

}
void Mundo::criaCelulaTerra(int x, int y)
{

	this->terra.push_back(new Terra(x, y));

}
void Mundo::criaCelulaPorto(int x, int y,char t)
{

	this->porto.push_back(new Porto(x, y, t));

}

const vector<const Mar*> Mundo::getVetorMar() const
{
	return vector<const Mar *>(this->mar.begin(), this->mar.end());
}

const vector<const Terra*> Mundo::getVetorTerra() const
{
	return vector<const Terra *>(this->terra.begin(), this->terra.end());
}

const vector<const Porto*> Mundo::getVetorPorto() const
{
	return vector<const Porto *>(this->porto.begin(), this->porto.end());
}
const vector<const Navios*> Mundo::getVetorNavios() const
{
	return vector<const Navios *>(this->navios.begin(), this->navios.end());
}

Mundo::~Mundo()
{
}
