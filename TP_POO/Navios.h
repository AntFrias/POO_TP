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
	int x, y;
	static int IncNavio;
	int id;
	int preco;
	char tipo;
	int quantSoldados;
	int quantAgua;


public:
	Navios();
	/*Navios(int preco, int tipo, int quantSoldados, int quantAgua);*/
	Navios(char tipo, const int x, const int y);
	const int getX()const;
	const int getY()const;
	void setX(int x);
	const int getId()const;
	int getIncNavio();
	void setY(int y);
	~Navios();


};



#endif //NAVIOS_H

