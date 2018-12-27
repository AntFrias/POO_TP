#ifndef CALMARIA_H
#define CALMARIA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "Eventos.h"

#define EVENTO_CALMARIA 3

#define CALMARIA_ESTADO_INICIO_CALMARIA 1
#define CALMARIA_ESTADO_FIM_CALMARIA 2

#define EVENTO_EXECUCAO_COMANDO 1
#define EVENTO_EXECUCAO_RAND 2

using namespace std;

class Calmaria : public Eventos
{
public:
	Calmaria(Mundo *mundo) : Eventos(mundo, EVENTO_CALMARIA) {};
	string TrataEvento(int modoExecucao, int idNavio, int coordX, int coordY, int duracao);
	virtual bool VerificaEventoCalmaria() { return true; };

	virtual int getTTL() const;
	virtual void setTTL();
	
	~Calmaria();
};
#endif // !CALMARIA_H
