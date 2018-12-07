#ifndef MUNDO_H
#define MUNDO_H
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

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

	vector<Mar*> mar; 
	vector<Terra*> terra;
	vector<Porto*> porto;
	vector<Navios*> navios;


public:

	Mundo();

	const char getPortoPrincipal();
	
	Navios & criaNavio(Mundo *mundo,char tipo);

	void criaCelulaMar(int x,int y);

	void criaCelulaTerra(int x, int y);

	void criaCelulaPorto(int x, int y,char t);

	const vector < const Mar *> getVetorMar() const;

	const vector<const Terra*> getVetorTerra() const;

	const vector<const Porto*> getVetorPorto() const;

	const vector<const Navios*> getVetorNavios() const;
	
	int verificaCelula(int x, int y);

	Navios * getNavio(int id);

	void setDimX(int xMax);

	void setDimY(int yMax);

	const int getDimX() const;

	const int getDimY() const;

	~Mundo();
};


#endif //MUNDO_H
