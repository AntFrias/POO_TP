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

#define PRECO_VELEIRO 100
#define PRECO_GALEAO 220
#define PRECO_ESCUNA 150
#define PRECO_FRAGATA 5
#define PRECO_SUBMARINO 500

#define COMPRA_COM_SUCESSO 0
#define COMPRA_SEM_MOEDAS -1
#define TIPO_NAVIO_INVALIDO -2



enum IndiceComandos {
	com_exec = 1,
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
	com_delg,
};
enum IndiceConFiguracoes {


	nlinhas = 1,
	ncolunas,
	nmoedas,
	probpirata,
	preconavio,
	precosoldado,
	precovendpeixe,
	precocompmercad,
	precovendmercad,
	soldadosporto,
	probevento,
	probtempestade,
	probsereias,
	probcalmaria,
	probmotin
};

class Interface
{
	Mundo mundo;

	Jogador jogador;

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
	void PromptFase2(string linha);
	int ValidaCompraJogador(char tipoNavio);
	int compraNavio(char tipo);
	void Prompt();
	void mostraLegAndConfig();
	void mostraMar();
	void mostraTerra();
	void mostraPortos();
	void mostraNavios();
	void mostraNaviosJogador();
	void start();
	void gotoComando();
	void gotoErro();
	void gotoPrint();
	void mostraMapa();
	bool ativoModeAuto(int idNavio);
	bool desativoModeAuto(int idNavio);
	int verificaDadosFicheiro(string linha);
	bool carregaFich(string configfich);



	~Interface();
};

#endif //INTERFACE_H