#include "Galeao.h"





void Galeao::AbasteceAguaNavio()
{
	this->quantAgua = GALEAO_MAX_AGUA;
}

bool Galeao::VerificaCargaNavio(int novaCarga)
{
	if (this->QuantMercadoria + novaCarga <= GALEAO_QUANT_MAX_CARGA)
		return true;
	else
		return false;
}
bool Galeao::souGaleao() {
	return true;
}

Galeao::~Galeao()
{
}
