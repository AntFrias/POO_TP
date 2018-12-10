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

#include "Mar.h"
#include "Terra.h"
#include "Porto.h"
#include "Navios.h"



enum movimentosNavios {
	
	naoMove = 0,
	moveCima,
	moveBaixo,
	moveEsquerda,
	moveDireita,
	moveCimaEsquerda,
	moveCimaDireita,
	moveBaixoEsquerda,
	moveBaixoDireita
	
};

enum TiposNavios {

	FRAGATA = 1,
	ESCUNA,
	VELEIRO,
	GALEAO

};

using namespace std;

class Jogador;

class Mundo {

	int dimX;
	int dimY;

	vector<Superficie*> superficie;
	vector<Porto*> porto;
	vector<Navios*> navios;


public:

	Mundo();

	int ValidaTipoNavio(const char tipo);

	const char getPortoPrincipal();
	
	Navios & criaNavio(Mundo *mundo,char PortoPrincipal, char tipoNavio);

	//void criaCelulaMar(int x,int y);

	//void criaCelulaTerra(int x, int y);

	void criaSuperficie(int x, int y, char tipo);

	void criaCelulaPorto(int x, int y,char t);

	const vector<const Superficie*> getVetorSuperficie() const;

	const vector<const Porto*> getVetorPorto() const;

	const vector<const Navios*> getVetorNavios() const;
	
	int verificaCelulaMar(int x, int y);

	int verificaCelulaNavio(int x, int y);

	Navios * getNavio(int id);

	void setDimX(int xMax);

	void setDimY(int yMax);

	const int getDimX() const;

	const int getDimY() const;

	int verificaCelulaPortoAmigo(int x, int y);

	~Mundo();
};


#endif //MUNDO_H
