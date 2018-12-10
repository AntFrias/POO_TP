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
#define CELULA_NAVIO 4

#define MOVE_INVALIDO 0
#define MOVE_VALIDO 1

#define DESLOCAMENTO_NAVIO_BASE 0
#define DESLOCAMENTO_NAVIO_RAPIDO 1

#define VELEIRO_QUANT_MAX_CARGA 40
#define GALEAO_QUANT_MAX_CARGA 70
#define ESCUNA_QUANT_MAX_CARGA 20
#define FRAGATA_QUANT_MAX_CARGA 0

#define VELEIRO_MAX_AGUA 200
#define GALEAO_MAX_AGUA 400
#define ESCUNA_MAX_AGUA 100
#define FRAGATA_MAX_AGUA 500

using namespace std;

class Mundo;

class Navios
{




protected:

	static int IncNavio;
	int id;
	Mundo *mundo;
	bool autoMove;
	int x, y;
	char tipo;
	int quantSoldados;
	int quantAgua;


public:
	Navios();
	/*Navios(int preco, int tipo, int quantSoldados, int quantAgua);*/
	Navios(Mundo *mundo, char tipo,int x,int y, int quantSoldados, int quantAgua = 0, int autoMove = false);
	int moveNavio(int direcao);
	int getX()const;
	int getY()const;
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

