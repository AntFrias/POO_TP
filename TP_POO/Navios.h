#ifndef NAVIOS_H
#define NAVIOS_H
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#define CELULA_MAR 1 
#define CELULA_TERRA 2 
#define CELULA_PORTO 3

#define INVAL_MOVE 0
#define VAL_MOVE 1

using namespace std;

class Mundo;

class Navios
{
	Mundo *mundo;
	int x, y;
	static int IncNavio;
	int id;
	bool autoMove;
	int preco;
	char tipo;
	int quantSoldados;
	int quantAgua;


public:
	Navios();
	/*Navios(int preco, int tipo, int quantSoldados, int quantAgua);*/
	Navios(Mundo *mundo, char tipo,int x,int y, int autoMove = 0);
	int moveNavio(int direcao);
	const int getX()const;
	const int getY()const;
	void setX(int x);
	void setY(int y);
	void setAutoMove(bool move);
	int getAutoMove();
	const int getId()const;
	const Navios getNavio() const;	
	int getIncNavio();
	
	~Navios();


};



#endif //NAVIOS_H

