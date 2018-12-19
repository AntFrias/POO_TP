#include "Navios.h"
#include "Mundo.h"

Navios::Navios()
{
}

Navios::Navios(Mundo *mundo, char tipo,bool pirata, int x, int y, int quantSoldados, int quantAgua, bool calmaria, bool autoMove, bool atracado,bool afundado)
{
	this->mundo = mundo;
	this->id = this->IncNavio++;
	this->tipo = tipo;
	this->pirata = pirata;
	this->quantAgua = quantAgua;
	this->quantSoldados = quantSoldados;
	this->Calmaria = calmaria;
	this->autoMove = autoMove;
	this->Atracado = atracado;
	this->afundado = false;
	this->x = x;
	this->y = y;
}
bool Navios::getCalmaria() const
{
	return this->Calmaria;
}
void Navios::setCalmaria(bool estado)
{
	this->Calmaria = estado;
}
void Navios::SetMotim(bool estado)
{
	this->Motim = estado;
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
void Navios::setNavioDeriva()
{
	autoMove = true;
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
string Navios::AlteraSoldadosPosEvento(int prob)
{
	ostringstream os;

	int soldadosPerdidos = (quantSoldados * prob) / 100;
	os << "Total de Soldados Antes do ataque: " << this->quantSoldados << endl;
	quantSoldados = quantSoldados - soldadosPerdidos;

	os << "Quantidade Soldados Perdidos pelo navio" << this->id << ": " << soldadosPerdidos << endl;
	os << "Total de Soldados que permanecem no navio : " << this->quantSoldados << endl;

	if (quantSoldados == 0 )
		this->autoMove = true;

	return os.str();
}

Navios::~Navios()
{
}
