#ifndef JOGADOR_H
#define JOGADOR_H
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "Navios.h"

#include "Porto.h"


#define AUTOMOVE_ON 1
#define AUTOMOVE_OFF 0

using namespace std;

class Jogador
{

	int moedas;

	char portoPrincipal;

	vector<Navios*> navios;
	vector<Porto*> portos;

public:
	
	Jogador();

	void setMoedas(int moedas);

	const int getMoedas() const;

	bool validaCompra(int valor);

	void setPortoPrincipal(char tipo);

	const char getPortoPrincipal();

	void addNavioJogador(Navios * navio);

	bool verificaModoAutomaticoNavio(int idNavio);

	int moveNavioJogador(int id, int direcao);

	void moveNavioAuto();

	bool validaIdNavio(int idNavio);

	void AlteraAutoMoveNavio(int idNavio, int autoMove);

	const vector<const Navios*> getVetorNaviosJogador() const;

	~Jogador();
};


#endif //JOGADOR_H
