#include "Eventos.h"
#include "Mundo.h"





Eventos::Eventos(Mundo *mundo, int TTL)
{
	
	this->mundo = mundo;
	this->TTL = TTL;

}
Eventos::~Eventos()
{
}
