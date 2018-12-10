#include "Escuna.h"



void Escuna::AbasteceAguaNavio()
{
	this->quantAgua = ESCUNA_MAX_AGUA;
}

bool Escuna::VerificaCargaNavio(int novaCarga)
{
	if (this->QuantMercadoria + novaCarga <= ESCUNA_QUANT_MAX_CARGA)
		return true;
	else
		return false;
}

Escuna::~Escuna()
{
}
