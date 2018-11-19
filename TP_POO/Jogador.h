#ifndef JOGADOR_H
#define JOGADOR_H
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "Navios.h"


using namespace std;

class Jogador
{

	int moedas;

	vector<Navios*> navios;

public:
	
	Jogador();

	Jogador(int moedas);

	~Jogador();
};


#endif //JOGADOR_H
