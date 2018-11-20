#include "Navios.h"


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
Navios::Navios(char tipo,int x,int y) {

	this->id = this->IncNavio++;
	this->tipo = tipo;

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

int Navios::getIncNavio() {
	return this->IncNavio;
}

void Navios::setY(int y) {

	this->y=y;
}

Navios::~Navios()
{
}
