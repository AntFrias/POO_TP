#include "Navios.h"
#include "Mundo.h"

Navios::Navios()
{
}
int Navios::getEstado()const {
	return this->estado;
}
void Navios::setEstado(int estado) {
	this->estado = estado;
}
Navios::Navios(Mundo *mundo, char tipo, int x, int y, int quantSoldados, int quantAgua, int estado)
{
	this->mundo = mundo;
	this->id = this->IncNavio++;
	this->tipo = tipo;
	this->quantAgua = quantAgua;
	this->quantSoldados = quantSoldados;
	this->estado = estado;
	this->x = x;
	this->y = y;
}


int Navios::randNumber(int nSoldados) {

	if (nSoldados > 0) {
		return rand() % nSoldados + 1;
	}
	return 0;
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
void Navios::setY(int y) {

	this->y = y;
}
int Navios::getXvaiPara()const {

	return this->xVaiPara;
}
int Navios::getYvaiPara()const {

	return this->yVaiPara;
}
void Navios::setXvaiPara(int x) {

	this->xVaiPara = x;
}
void Navios::setYvaiPara(int y) {

	this->yVaiPara = y;
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
string Navios::AlteraSoldadosPosEvento(int prob)
{
	ostringstream os;

	int soldadosPerdidos = (quantSoldados * prob) / 100;
	os << "Total de Soldados Antes do ataque de Sereias : " << this->quantSoldados << endl;
	quantSoldados = quantSoldados - soldadosPerdidos;

	os << "Quantidade Soldados Perdidos pelo navio apos ataque " << this->id << ": " << soldadosPerdidos << endl;
	os << "Total de Soldados que permanecem no navio : " << this->quantSoldados << endl;

	if (quantSoldados <= 0 )
		this->estado = aDeriva;

	return os.str();
}

Navios::~Navios()
{
}
