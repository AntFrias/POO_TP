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
	bool autoMove;
	int preco;
	char tipo;
	int quantSoldados;
	int quantAgua;


public:
	Navios();
	/*Navios(int preco, int tipo, int quantSoldados, int quantAgua);*/
	Navios(char tipo,int x,int y, int autoMove = 0);
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

