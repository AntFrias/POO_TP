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

#define CELULA_MAR 1 
#define CELULA_TERRA 2 
#define CELULA_PORTO 3

#define AUTOMOVE_ON 1
#define AUTOMOVE_OFF 0

#define INVAL_MOVE 0
#define VAL_MOVE 1

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

	int moveNavio(int id, int direcao);
	
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

	bool validaIdNavio(int idNavio);

	void AlteraAutoMoveNavio(int idNavio, int autoMove);

	bool verificaModoAutomaticoNavio(int idNavio);

	void setDimX(int xMax);

	void setDimY(int yMax);

	const int getDimX() const;

	const int getDimY() const;

	void moveNavioAuto();

	~Mundo();
};


#endif //MUNDO_H
