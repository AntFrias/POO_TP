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

using namespace std;

class Mundo {


	vector<Mar*> mar; 
	vector<Terra*> terra;
	vector<Porto*> porto;
	vector<Navios*> navios;


public:
	Mundo();

	const char getPortoPrincipal();
	
	void criaNavio(char tipo);
	void criaCelulaMar(int x,int y);

	void criaCelulaTerra(int x, int y);

	void criaCelulaPorto(int x, int y,char t);

	const vector < const Mar *> getVetorMar() const;

	const vector<const Terra*> getVetorTerra() const;

	const vector<const Porto*> getVetorPorto() const;

	const vector<const Navios*> getVetorNavios() const;


	~Mundo();
};


#endif //MUNDO_H
