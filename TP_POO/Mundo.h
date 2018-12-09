#ifndef MUNDO_H
#define MUNDO_H
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "Superficie.h"
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

	const char getPortoPrincipal();
	
	Navios & criaNavio(Mundo *mundo,char tipo);

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

	~Mundo();
};


#endif //MUNDO_H
