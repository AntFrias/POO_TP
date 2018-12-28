#ifndef INTERFACE_H
#define INTERFACE_H


#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <iomanip>

#include "Mundo.h"
#include "Consola.h"
#include "Jogador.h"


using namespace std;


#define configInit "configIni.txt"


#define FICHEIROCONFIGERROR 1 

#define PRECO_VELEIRO 100
#define PRECO_GALEAO 220
#define PRECO_ESCUNA 150
#define PRECO_FRAGATA 100
#define PRECO_TARTARUGA 500

#define COMPRA_COM_SUCESSO 0
#define COMPRA_SEM_MOEDAS -1
#define TIPO_NAVIO_INVALIDO -2

#define EVENTO_TEMPESTADE 1
#define EVENTO_SEREIAS 2
#define EVENTO_CALMARIA 3
#define EVENTO_MOTIM 4

#define EVENTO_EXECUCAO_COMANDO 1
#define EVENTO_EXECUCAO_RAND 2

// para diferenciar a insercao de eventos por comandos
#define INSERCAO_COMANDO true
#define INSERCAO_RAND false

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

	int Turno;
	static int incTurno;
	bool InsercaoEvento;

public:
	Interface() : Turno(0) {};
	int FiltaComandos(string acao);
	void PromptFase1(string linha);
	void PromptFase2(string linha);
	int ValidaCompraJogador(char tipoNavio);
	int compraNavio(char tipo);
	int ValidaDirecoes(string direcao);
	void Prompt();
	void mostraLegAndConfig();
	void mostraSuperficie();
	void mostraPortos();
	void mostraNavios();
	void mostraNaviosJogador();
	void start();
	void acrescentaMoedas(int moedas);
	void gotoComando();
	void gotoErro();
	void gotoPrint();
	void criaPiratasAuto();
	string mostraInformacaoPortos();
	string ExecutaEventos();
	string GeradorEvento(int ModoExecucao, int tipoEvento, int idNavio, int coordX, int coordY);
	int verificaFimdoJogo();
	void mostraMapa();
	int verificaDadosFicheiro(string linha);
	bool carregaFich(string configfich);
	bool getInsercaoComandoEvento() const;
	void setInsercaoComandoEvento(bool insercao);
	



	~Interface();
};

#endif //INTERFACE_H