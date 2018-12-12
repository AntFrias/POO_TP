#include "Mar.h"



char Mar::getTipo() const
{
	return this->tipo;
}

void Mar::PescaCardumeMar(int turnoPescaria)
{
	this->TurnoPesca = turnoPescaria;
	this->CardumePeixe = false;
}
bool Mar::VerificaCelulaMar()const{

	return true;

}
bool Mar::VerificaCelulaTerra()const {

	return false;

}
void Mar::VerificaRegenacaoPeixe(int TurnoAtual)
{
	if (this->CardumePeixe == false && TurnoAtual - this->TurnoPesca == TEMPO_REGENERACAO_PEIXE)
		this->CardumePeixe = true;
}

bool Mar::VerificaCardumePeixe()
{
	if (this->CardumePeixe == true)
		return true;
	else
		return false;
}

Mar::~Mar()
{
}
