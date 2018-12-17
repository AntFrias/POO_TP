#ifndef MUNDO_H
#define MUNDO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "Superficie.h"
#include "Veleiro.h"
#include "Galeao.h"
#include "Escuna.h"
#include "Fragata.h"

#include "Calmaria.h"
#include "Motim.h"

#include "Mar.h"
#include "Terra.h"
#include "Porto.h"
#include "Navios.h"

#define EVENTO_ON true
#define EVENTO_OFF false

#define EVENTO_TEMPESTADE 1
#define EVENTO_SEREIAS 2
#define EVENTO_CALMARIA 3
#define EVENTO_MOTIM 4

enum TiposNavios {

	FRAGATA = 1,
	ESCUNA,
	VELEIRO,
	GALEAO

};

using namespace std;

class Eventos;

class Jogador;

class Mundo {

	int dimX;
	int dimY;

	bool EstadoEvento;
	Eventos *Evento;

	vector<Superficie*> superficie;
	vector<Porto*> porto;
	vector<Navios*> navios;

public:

	Mundo(){};

	int portosBemColocado();

	int ValidaTipoNavio(const char tipo);

	const char getPortoPrincipal();
	
	Navios & criaNavio(Mundo *mundo,char PortoPrincipal, char tipoNavio);

	void criaSuperficie(int x, int y, char tipo);

	void criaCelulaPorto(int x, int y,char t);

	void retiraNavAfundados();

	const vector<const Superficie*> getVetorSuperficie() const;

	const vector<const Porto*> getVetorPorto() const;

	const vector<const Navios*> getVetorNavios() const;
	
	int verificaCelulaMar(int x, int y);

	int verificaCelulaNavio(int x, int y);

	Navios * getNavio(int id);

	Navios * getNavioXY(int x, int y);

	void setDimX(int xMax);

	void setDimY(int yMax);

	const int getDimX() const;

	const int getDimY() const;

	bool getExistenciaEvento() const;

	void setExistenciaEvento(bool estado);

	void setEventoEmExecucao(Eventos *evento);
	
	int TrataEventoTempestade(int x, int y);

	void TrataEventos(int TipoEvento = 0);

	void criaEvento(Mundo *mundo, int tipo);

	void limpaVetores();

	int verificaCelulaPorto(int x, int y);

	~Mundo();
};


#endif //MUNDO_H
