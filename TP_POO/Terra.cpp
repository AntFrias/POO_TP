#include "Terra.h"


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
