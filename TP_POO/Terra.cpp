#include "Terra.h"


Terra::Terra()
{
}
Terra::Terra(const Terra &aux) {

	this->tipo = aux.tipo;
	this->x = aux.x;
	this->y = aux.y;

}
Terra * Terra::Duplica() const
{
	return new Terra(*this);
}
char Terra::getTipo() const
{
	return this->tipo;
}
void Terra::PescaCardumeMar(int turnoPescaria)
{
}
void Terra::VerificaRegenacaoPeixe(int TurnoAtual)
{
}
bool Terra::VerificaCardumePeixe()const
{
	return false;
}
bool Terra::VerificaCelulaMar()const{

	return false;

}
bool Terra::VerificaCelulaTerra()const {

	return true;

}

Terra::~Terra()
{
}
