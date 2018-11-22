#ifndef JOGADOR_H
#define JOGADOR_H
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "Navios.h"

#include "Porto.h"


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

	const vector<const Navios*> getVetorNaviosJogador() const;

	~Jogador();
};


#endif //JOGADOR_H
