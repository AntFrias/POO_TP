#include "Mar.h"

using namespace std;

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
	if (this->celulaPeixe == true && TurnoAtual - this->TurnoPesca == TEMPO_REGENERACAO_PEIXE){
		this->TurnoPesca = 0;
		this->CardumePeixe = true;
	}

}

bool Mar::VerificaCardumePeixe()const
{
	if (this->CardumePeixe == true){
		return true;
	}
	else
		return false;
}

bool Mar::VerificaCelulaPeixe()const
{
	return this->celulaPeixe;
}

Mar::~Mar()
{
}
