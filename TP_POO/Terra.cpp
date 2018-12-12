#include "Terra.h"


char Terra::getTipo() const
{
	return this->tipo;
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
