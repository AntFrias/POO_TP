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

#define NAVIO_AFUNDADO true

#define PROB_FRAGATA_AFUNDAR_TEMPESTADE 20
#define PROB_ESCUNA_AFUNDAR_TEMPESTADE 35 
#define PROB_VELEIRO_AFUNDAR_TEMPESTADE_1 35
#define PROB_VELEIRO_AFUNDAR_TEMPESTADE_2 20
#define PROB_GALEAO_AFUNDAR_TEMPESTADE 40

#define PROB_SEREIAS_AFETAR_SOLDADOS 10

#define PROB_ESCUNA_PERDER_CARGA 20
#define PROB_VELEIRO_PERDER_CARGA 50

#define EVENTO_TEMPESTADE 1
#define EVENTO_SEREIAS 2
#define EVENTO_CALMARIA 3
#define EVENTO_MOTIM 4

#define MOTIM_ESTADO_INICIO_MOTIM 1
#define MOTIM_ESTADO_FIM_MOTIM 2

#define CALMARIA_ESTADO_EM_EXECUCAO_CALMARIA 1
#define CALMARIA_ESTADO_FIM_CALMARIA 2

#define RANGE_EVENTO 2

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

	void abasteceNaviosNosPortos();

	void verificaaDeriva();

	void mudaPorto(int xPorto, int yPorto, char letra);

	char LastPortoAmigo();

	char LastPortoInimigo();

	int ValidaTipoNavio(const char tipo);

	int ValidaTipoNavioP(const char tipo);

	const char getPortoPrincipal();
	
	Navios & criaNavio(Mundo *mundo,char PortoPrincipal, char tipoNavio);

	string moveNavioPirataAuto();

	void criaNavPirata(Mundo *mundo, const char TipoNavio, int x, int y);

	void criaSuperficie(int x, int y, char tipo);

	void criaCelulaPorto(int x, int y,char t);

	void retiraNavAfundados();

	const vector<const Superficie*> getVetorSuperficie() const;

	const vector<const Porto*> getVetorPorto() const;

	const vector<const Navios*> getVetorNavios() const;
	
	int verificaCelulaMar(int x, int y);

	int verificaCelulaNavio(int x, int y);

	int verificaCelulaNavioPirata(int x, int y);

	int verificaCelulaNavioDeriva(int x, int y);

	Navios * getNavio(int id);

	Navios * getNavioXY(int x, int y);

	void setDimX(int xMax);

	void setDimY(int yMax);

	const int getDimX() const;

	const int getDimY() const;

	bool getExistenciaEvento() const;

	void setExistenciaEvento(bool estado);

	void setEventoEmExecucao(Eventos *evento);

	string TrataEventoMotim(int estadoMotim);

	bool VerificaTipoEventoEmExecucao() { return Evento->VerificaEventoCalmaria(); };

	string TrataEventoCalmaria(int epiX, int epiY, int estadoCalmaria);

	string TrataEventoSereias(int indice);
	
	string TrataEventoTempestade(int x, int y);

	string trataEventos(int TipoEvento = 0);

	string criaEvento(Mundo *mundo, int tipo);

	bool VerificaExistenciaNavios();

	void limpaVetores();

	int verificaCelulaPorto(int x, int y);

	~Mundo();
};


#endif //MUNDO_H
