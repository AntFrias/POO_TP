#include "Navios.h"
#include "Mundo.h"

Navios::Navios()
{
}

//Navios::Navios(int preco,int tipo,int quantSoldados,int quantAgua){
//
//	this->id = ++this->IncNavio;
//	this->preco = preco;
//	this->tipo = tipo;
//	this->quantSoldados = quantSoldados;
//	this->quantAgua = quantAgua;
//}

Navios::Navios(Mundo *mundo, char tipo, int x, int y, int autoMove)
{
	this->mundo = mundo;
	this->id = this->IncNavio++;
	this->tipo = tipo;
	this->autoMove = autoMove;
	this->x = x;
	this->y = y;
}


const int Navios::getX()const {

	return this->x;
}
const int Navios::getY()const {

	return this->y;
}
void Navios::setX(int x) {

	this->x=x;
}
const int Navios::getId()const {
	return this->id;
}

const Navios Navios::getNavio() const
{
	return *this;
}

int Navios::getIncNavio() {
	return this->IncNavio;
}

void Navios::setY(int y) {

	this->y=y;
}
void Navios::setAutoMove(bool move) {
	this->autoMove = move;
}
int Navios::getAutoMove() {
	return this->autoMove;
}

Navios::~Navios()
{
}
