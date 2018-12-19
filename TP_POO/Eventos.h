#ifndef EVENTOS_H
#define EVENTOS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#define TTL_TEMPESTADE 1
#define TTL_SEREIA 1
#define TTL_CALMARIA 3
#define TTL_MOTIM 4

class Mundo;

using namespace std;

class Eventos
{


protected:
	Mundo *mundo;
	int TTL;

public:

	Eventos(Mundo *mundo, int TTL);
	virtual bool VerificaEventoCalmaria() = 0;
	virtual string TrataEvento() = 0;
	virtual int getTTL()const = 0;
	~Eventos();
};
#endif // !EVENTOS_H
