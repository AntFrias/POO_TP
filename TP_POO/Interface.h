#ifndef INTERFACE_H
#define INTERFACE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "Mundo.h"
#include "Consola.h"
#include "Jogador.h"

using namespace std;
#define configInit "configIni.txt"
#define FICHEIROCONFIGERROR 1 

enum IndiceComandos {
	com_config = 1,
	com_exec,
	com_prox,
	com_compranav,
	com_vendenav,
	com_lista,
	com_compra,
	com_vende,
	com_move,
	com_auto,
	com_stop,
	com_pirata,
	com_evpos,
	com_evnav,
	com_moedas,
	com_vaipara,
	com_comprasold,
	com_saveg,
	com_loadg,
	com_delg
};

class Interface
{
	Mundo mundo;

	Jogador jogador;

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
	int FiltaComandos(string acao);
	void PromptFase1(string linha);
	void PromptFase2(string acao);
	void Prompt();
	void mostraLegAndConfig();
	void mostraMar();
	void mostraTerra();
	void mostraPortos();
	void start();
	void mostraMapa();
	bool carregaFich(string configfich);

	~Interface();
};

#endif //INTERFACE_H