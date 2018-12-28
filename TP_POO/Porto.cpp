#include "Porto.h"

Porto::Porto(int x, int y, char tipoPorto, int nSoldados, int tMercadoria)
{
	this->TipoPorto = tipoPorto;
	this->x = x;
	this->y = y;
	this->numSoldados = nSoldados;
	this->Mercadoria = tMercadoria;
	
}
bool Porto::verificaPortoAmigo() {

	if ((this->TipoPorto >= 'A' && this->TipoPorto <= 'Z'))
		return true;
	else
	return false;	
}
void Porto::setMercadoria(int tMercadoria)
{
	this->Mercadoria = tMercadoria;
}
int Porto::getMercadoria() const
{
	return this->Mercadoria;
}
void Porto::setNumSoldados(int nSoldados)
{
	this->numSoldados = nSoldados;
}
int Porto::getNumSoldados() const
{
	return this->numSoldados;
}
const int Porto::getX() const {

	return this->x;
}
const int Porto::getY() const {

	return this->y;
}
void Porto::setX(int x)  {

	this->x = x;
}
void Porto::setY(int y) {

	this->y = y;
}
void Porto::MudaTipoPorto(char letra) {
	this->TipoPorto = letra;
}
const char Porto::getChar() const {

	return this->TipoPorto;
}
Porto & Porto::getPorto()
{
	return *this;
}
string Porto::getInfoPorto() {

	ostringstream os;
	
	os << "_________________________________________________________________" << endl;
	if (this->TipoPorto >= 'A' && this->TipoPorto <= 'Z')
		os << " Relacao de Amizade : Porto Amigo { " << this->TipoPorto << " } "<< endl;
	else
		os << " Relacao de Amizade : Porto Inimigo { " << this->TipoPorto << " } " << endl;
	os << " Quantidade de Soldados : " << this->numSoldados << endl;
	os << " Quantidade de Mercadoria : " << this->Mercadoria << endl;
	os << "_________________________________________________________________" << endl;

	return os.str();
}

Porto::~Porto()
{
}
