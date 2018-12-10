#include "Veleiro.h"



void Veleiro::AbasteceAguaNavio()
{
	this->quantAgua = VELEIRO_MAX_AGUA;
	
}

bool Veleiro::VerificaCargaNavio(int novaCarga)
{
	if (this->QuantMercadoria + novaCarga <= VELEIRO_QUANT_MAX_CARGA)
		return true;
	else
		return false;
}

Veleiro::~Veleiro()
{
}
