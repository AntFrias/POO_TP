#include "Navios.h"
#include "Mundo.h"

Navios::Navios()
{
}

Navios::Navios(Mundo *mundo, char tipo, int x, int y, int quantSoldados, int quantAgua, bool autoMove, bool atracado,bool afundado)
{
	this->mundo = mundo;
	this->id = this->IncNavio++;
	this->tipo = tipo;
	this->quantAgua = quantAgua;
	this->quantSoldados = quantSoldados;
	this->autoMove = autoMove;
	this->Atracado = atracado;
	this->afundado = false;
	this->x = x;
	this->y = y;
}
int Navios::randNumber(int nSoldados) {

	if (nSoldados > 0) {
		return rand() % nSoldados + 1;
	}
	return 0;
}
void Navios::setAfundado(bool result) {

	this->afundado = result;
}
bool Navios::getAfundado() {

	return this->afundado;
}

int Navios::getNumSoldados() {
	return this->quantSoldados;
}
void Navios::setNumSoldados(int num) {
	this->quantSoldados = num;
}

char Navios::getTipo() const
{
	return this->tipo;
}

int Navios::getX()const {
	
	return this->x;
}
int Navios::getY()const {

	return this->y;
}
void Navios::setX(int x) {

	this->x=x;
}
const int Navios::getId()const {
	return this->id;
}

const Navios * Navios::getNavio() const
{
	return this;
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

bool Navios::getNavioAtracado()
{
	return this->Atracado;
}

void Navios::setNavioAtracado(bool estado)
{
	this->Atracado = estado;
}

Navios::~Navios()
{
}
