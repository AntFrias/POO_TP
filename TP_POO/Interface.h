#ifndef INTERFACE_H
#define INTERFACE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "Mundo.h"
#include "Consola.h"

using namespace std;
#define configInit "configIni.txt"


class Interface
{
	Mundo mundo;

	int linhas, colunas;
	int moedas;
	int probPirata;
	int precoNavio;
	int precoSoldado;
	int precoVendePeixe;
	int precoCompraMercadoria;
	int precoVendaMercadoria;
	int soldadosPorto;
	int probVento;
	int probTempestade;
	int probSereias;
	int probCalmaria;
	int probMotin;

	

public:
	Interface();

	void start();
	void mostraMapa();
	void carregaFich();

	~Interface();
};

#endif //INTERFACE_H