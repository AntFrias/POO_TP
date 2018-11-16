#ifndef MUNDO_H
#define MUNDO_H
#include "Mar.h"
#include "Terra.h"
#include "Porto.h"
#include <vector>

class Mundo {

	Mar *mar; // vector <Mar *> mar;
	Terra *terra;
	Porto *porto;

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
	Mundo();
	Mundo(int linhas, int colunas,
		int moedas,
		int probPirata,
		int precoNavio,
		int precoSoldado,
		int precoVendePeixe,
		int precoCompraMercadoria,
		int precoVendaMercadoria,
		int soldadosPorto,
		int probVento,
		int probTempestade,
		int probSereias,
		int probCalmaria,
		int probMotin,
		Mar &m,
		Terra &t,
		Porto &p);

	~Mundo();
};


#endif //MUNDO_H
