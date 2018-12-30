#ifndef JOGADOR_H
#define JOGADOR_H
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "Navios.h"

#include "Porto.h"

#define AUTOMOVE_ON 1
#define AUTOMOVE_OFF 0

using namespace std;

class Mundo;

class Jogador
{
	Mundo *mundo;

	int moedas;

	char portoPrincipal;

	vector<Navios*> navios;
	//vector<Porto*> portos;

public:
	
	Jogador();

	void InterligaNaviosJogadorToMundo();

	void setPonteiroSaveMundo(Mundo * mundo);

	void EliminaJogadorGuardado();

	Jogador & operator=(const Jogador& aux);

	void setMundo(Mundo * mundo);

	Navios * getNavio(int id);

	Navios * getNavioJogador(int id);

	void mandaVaiPara();

	void setVaiPara(int idNavio, int x, int y);

	void setVaiPara(int idNavio, char tipo);

	void setMoedas(int moedas);

	const int getMoedas() const;

	void adicionaMoedas(int moedas);

	int vendeNavio(char tipo,int precoSoldado);

	bool validaCompra(int valor);

	void setPortoPrincipal(char tipo);

	const char getPortoPrincipal();

	void addNavioJogador(Navios * navio);

	bool verificaModoAutomaticoNavio(int idNavio);

	bool verificaNaviosJogador();

	int moveNavioJogador(int id, int direcao, int turnoJogo);

	string moveNavioAuto(int turnoAtual);

	bool validaIdNavio(int idNavio);

	void AlteraAutoMoveNavio(int idNavio, int estado);

	const vector<const Navios*> getVetorNaviosJogador() const;

	~Jogador();
};


#endif //JOGADOR_H
