#include "Mundo.h"
#include "Jogador.h"
using namespace std;


Mundo::Mundo() {

}

int Mundo::verificaCelula(int x, int y) {

	for (unsigned int i = 0; i < this->mar.size(); i++) {

		if (this->mar[i]->getX() == x && this->mar[i]->getY() == y)
			return CELULA_MAR;
	}

	return 0;
}

Navios & Mundo::criaNavio(Mundo *mundo,const char tipo) {

	int x, y;
	Navios *aux;
	for (unsigned int i = 0; i < porto.size(); i++) {

		if (porto[i]->getChar() == tipo) {

			x = porto[i]->getX();

			y = porto[i]->getY();
		}
	}
	aux = new Navios(mundo,tipo, x, y);
	
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

Navios * Mundo::getNavio(int id) {

	for (unsigned int i = 0; i < navios.size(); i++)
		if (navios[i]->getId() == id)
			return navios[i];

	return nullptr;
}
void Mundo::setDimX(int xMax) {
	this->dimX = xMax;
}
void Mundo::setDimY(int yMax) {
	this->dimY = yMax;
}
const int Mundo::getDimX()const {
	return this->dimX;
}
const int Mundo::getDimY() const{
	return this->dimY;
}
Mundo::~Mundo(){


	for (Mar *mar : mar)
		delete mar;

	for (Terra *terra : terra)
		delete terra;

	for (Porto *portos : porto)
		delete portos;
	
	for (Navios *navios : navios)
		delete navios;

}
