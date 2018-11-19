#ifndef NAVIOS_H
#define NAVIOS_H
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>


using namespace std;

class Navios
{
	int id;
	int preco;
	int tipo;
	int quantSoldados;
	int quantAgua;


public:
	Navios();
	~Navios();
};

#endif //NAVIOS_H

