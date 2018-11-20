#include "Interface.h"

using namespace std;

int Navios::IncNavio = 1;

Interface::Interface(){
}
void Interface::start() {


	Prompt();

}
// Metodo Prompt tem como objetivo tratar os comandos introduzidos pelo Jogador	
void Interface::Prompt() {

	string linha, acao, configFile;

	Consola::VERDE;

	Consola::gotoxy(0, 16);
	//cout << "Comando: config " << endl << endl;
	cout << "Comando: config ";

	getline(cin, linha);

	/*
	______________________________________________________________________________________

					iniciar a fase 1: trata comando config
	______________________________________________________________________________________
	*/
	PromptFase1(linha);
	//inicialização do jogador
		//moedas
	jogador.setMoedas(moedas);
		//atribuição do porto principal
	jogador.setPortoPrincipal( mundo.getPortoPrincipal() );
	//
	/*
	______________________________________________________________________________________

					iniciar a fase 2: Trata comandos do jogador
	______________________________________________________________________________________
	*/
	do {

		Consola::VERDE;

		Consola::gotoxy(0, 16);

		cout << "Comando: ";

		getline(cin, linha);

		PromptFase2(linha);
		
		//execução de comando pendentes | comportamentos automaticos
		//combates
		//eventos
		//piratas

		mostraMapa();

		Consola::getch();

		Consola::clrscr();

		mostraMapa();

	} while (linha != "sair");


}
int Interface::FiltaComandos(string acao) {

	vector< string > comandos = {"exec", "prox", "compranav", "vendenav", "lista", "compra", "vende", "move", "auto", "stop", "pirata","evpos","evnav",
								  "pirata", "evpos", "evnav","moedas","vaipara", "comprasold", "saveg", "loadg", "delg"};

	for (unsigned int i = 0; i < comandos.size(); i++) {
		if (comandos[i].compare(acao) == 0)
			return i + 1;
	}
	return 0;
}
void Interface::PromptFase1(string linha) {

	if (count(linha.begin(), linha.end(), ' ') == 0) {

		if (carregaFich(linha)) {
			cout << "Ficheiro introduzido carregado com sucesso .. !" << endl;
		}
		else {
			carregaFich(configInit);
			cout << " [ Erro ao carregar ficheiro ] Ficheiro por default carregado com Sucesso.. !" << endl;

		}
	}
	else {
		carregaFich(configInit);
		cout << " [ Erro ao carregar ficheiro ] Ficheiro por default carregado com Sucesso.. !" << endl;
	}
}

int Interface::verificaDadosFicheiro(string linha) {

	vector < string > dadosEntrada = { "linhas", "colunas" , "moedas" , "probpirata", "preconavio", "precosoldado", "precovendpeixe",  "precocompmercad" ,
										"precovendmercad", "soldadosporto", "probevento" , "probtempestade" , "probsereias" , "probcalmaria", "probmotin" };

	for (unsigned int i = 0; i < dadosEntrada.size(); i++) 
		if (linha.compare(dadosEntrada[i]) == 0)
			return i + 1;
	

	return 0;
}
bool Interface::carregaFich(string configFile) {

	fstream fp;

	int inteiro, contaLinhas = 0, flag = 0;
	string linha;

	
	if (!fp.is_open()) {
		fp.open(configFile);
		if (!fp.is_open())
			return false;
	}
	while (getline(fp, linha)) {

		istringstream buffer(linha);

		if (buffer >> linha && buffer >> inteiro) {

			switch (verificaDadosFicheiro(linha)) {

				case nlinhas:
					this->linhas = inteiro;
					break;
				case ncolunas:
					this->colunas = inteiro;
					break;
				case nmoedas:
					this->moedas = inteiro;
					break;
				case probpirata:
					this->probPirata = inteiro;
					break;
				case preconavio:
					this->precoNavio = inteiro;
					break;
				case precosoldado:
					this->precoSoldado = inteiro;
					break;
				case precovendpeixe:
					this->precoVendePeixe = inteiro;
					break;
				case precocompmercad:
					this->precoCompraMercadoria = inteiro;
					break;
				case precovendmercad:
					this->precoVendaMercadoria = inteiro;
					break;
				case soldadosporto:
					this->soldadosPorto = inteiro;
					break;
				case probevento:
					this->probVento = inteiro;
					break;
				case probtempestade:
					this->probTempestade = inteiro;
					break;
				case probsereias:
					this->probSereias = inteiro;
					break;
				case probcalmaria:
					this->probCalmaria = inteiro;
					break;
				case probmotin:
					this->probMotin = inteiro;
					break;
			}
		}
		else {
			buffer >> linha;
			for (int i = 0; i < this->colunas; i++) {
				if (linha[i] == '.') {

					this->mundo.criaCelulaMar(i, contaLinhas);
				}
				if (linha[i] == '+') {

					this->mundo.criaCelulaTerra(i, contaLinhas);
				}
				if (linha[i] >= 'A' && linha[i] <= 'Z' || linha[i] >= 'a' && linha[i] <= 'z') {

					this->mundo.criaCelulaPorto(i, contaLinhas, linha[i]);

				}
			}
			contaLinhas++;
		}
	}
	fp.close();

	return true;
}
int Interface::ValidaCompraJogador(char tipoNavio) {
	switch (tipoNavio) {
	case 'V':
		if (jogador.validaCompra(PRECO_VELEIRO)) {
			jogador.setMoedas((jogador.getMoedas() - PRECO_VELEIRO));
			return 0;
		}
		else
			return -1;
		break;
	case 'G':
		if (jogador.validaCompra(PRECO_GALEAO)) {
			jogador.setMoedas((jogador.getMoedas() - PRECO_GALEAO));
			return 0;
		}
		else
			return -1;
		break;
	case 'E':
		if (jogador.validaCompra(PRECO_ESCUNA)) {
			jogador.setMoedas((jogador.getMoedas() - PRECO_ESCUNA));
			return 0;
		}
		else
			return -1;
		break;
	case 'F':
		if (jogador.validaCompra(PRECO_FRAGATA)) {
			jogador.setMoedas((jogador.getMoedas() - PRECO_FRAGATA));
			return 0;
		}
		else
			return -1;
		break;
	case 'S':
		if (jogador.validaCompra(PRECO_SUBMARINO)) {
			jogador.setMoedas((jogador.getMoedas() - PRECO_SUBMARINO));
			return 0;
		}
		else
			return -1;
		break;
	}
	return -2;
}
int Interface::compraNavio(char tipo) {

	int validacaoCompra = 0;

	if (jogador.getPortoPrincipal() >= 'A' && jogador.getPortoPrincipal() <= 'Z') {

		validacaoCompra = ValidaCompraJogador(tipo);

		if (validacaoCompra == COMPRA_COM_SUCESSO)
			mundo.criaNavio(jogador.getPortoPrincipal());
	
	}
	return validacaoCompra;
}
void Interface::PromptFase2(string linha) {

	char tipo;
	string acao;
	istringstream buffer(linha);

	if (buffer >> acao){
		switch (FiltaComandos(acao)) {

		case com_exec:
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_prox:
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_compranav:
			buffer >> tipo;
				if (tipo =='V' || tipo == 'G' || tipo == 'E' || tipo == 'F' || tipo == 'S') {

					if (compraNavio(tipo) == COMPRA_COM_SUCESSO)
						cout << "Compra efetuada com sucesso!" <<endl;
					else if (compraNavio(tipo) == COMPRA_SEM_MOEDAS)
						cout << "Compra não efetuada <-> Jogador Sem Moedas" << endl;
					else if((compraNavio(tipo) == TIPO_NAVIO_INVALIDO))
						cout << "Compra não efetuada <-> Não existe porto principal" << endl;
				}
			else
				cout << "Parametro Tipo de Barco <T> Invalido" << endl;
				cout << "Saldo atual do Jogador: " << jogador.getMoedas() << endl;
				
			break;
		case com_vendenav:
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_lista:
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_compra:
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_vende:
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_move:
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_auto:
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_stop:
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_pirata:
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_evpos:
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_evnav:
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_moedas:
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_vaipara:
			//este comando tem overload devido aos parametros vaipara <N> <x> <y> e vai para <N> <P>
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_comprasold:
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_saveg:
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_loadg:
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		case com_delg:
			cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
			break;
		default:
			if(acao != "sair")
				cout << " [ ERRO ] Comando Incorreto..!" << endl;
			
		}
}
}
void Interface::mostraLegAndConfig() {

	Consola::setTextColor(Consola::BRANCO);

	Consola::gotoxy(25, 0);
	cout << "Legenda do Mapa";

	Consola::gotoxy(25, 2);
	cout << "\tMar -> azul";

	Consola::gotoxy(25, 3);
	cout << "\tTerra -> amarelo";

	Consola::gotoxy(25, 4);
	cout << "\tPortos -> A-Z Amigos";

	Consola::gotoxy(25, 5);
	cout << "\tPortos -> a-z Inimigos";

	Consola::gotoxy(60, 0);
	cout << "Moedas: " << this->moedas;
	Consola::gotoxy(60, 1);
	cout << "Probalidade Pirata " << this->probPirata;
	Consola::gotoxy(60, 2);
	cout << "Preco Navio " << this->precoNavio;
	Consola::gotoxy(60, 3);
	cout << "Preco Soldado " << this->precoSoldado;
	Consola::gotoxy(60, 4);
	cout << "Preco Vende Peixe " << this->precoVendePeixe;
	Consola::gotoxy(60, 5);
	cout << "Preco Compra Mercadoria " << this->precoCompraMercadoria;
	Consola::gotoxy(60, 6);
	cout << "Preco Vende Mercadoria " << this->precoVendaMercadoria;
	Consola::gotoxy(60, 7);
	cout << "Soldados Porto " << this->soldadosPorto;
	Consola::gotoxy(60, 8);
	cout << "Probabilidade Vento " << this->probVento;
	Consola::gotoxy(60, 9);
	cout << "Probabilidade Tempestade " << this->probTempestade;
	Consola::gotoxy(60, 10);
	cout << "Probabilidade Sereias " << this->probSereias;
	Consola::gotoxy(60, 11);
	cout << "Probabilidade Calmaria " << this->probCalmaria;
	Consola::gotoxy(60, 12);
	cout << "Probabilidade Motin " << this->probMotin;

}
void Interface::mostraMar() {
	
	const vector <const Mar *>  auxMar = mundo.getVetorMar();

	for (unsigned int i = 0; i < auxMar.size(); i++) {
		unsigned int x = auxMar[i]->getX();
		unsigned int y = auxMar[i]->getY();

		Consola::gotoxy(x, y);
		Consola::setTextColor(Consola::AZUL_CLARO);
		cout << char(254);
	}

}
void Interface::mostraTerra() {

	const vector <const Terra *>  auxTerra = mundo.getVetorTerra();

	for (unsigned int i = 0; i < auxTerra.size(); i++) {
		unsigned int x = auxTerra[i]->getX();
		unsigned int y = auxTerra[i]->getY();

		Consola::gotoxy(x, y);
		Consola::setTextColor(Consola::AMARELO);
		cout << char(254);
		//cout << auxTerra[i]->getChar();
	}
}
void Interface::mostraPortos() {

	const vector <const Porto *>  auxPorto = mundo.getVetorPorto();

	for (unsigned int i = 0; i < auxPorto.size(); i++) {
		unsigned int x = auxPorto[i]->getX();
		unsigned int y = auxPorto[i]->getY();

	
			if (auxPorto[i]->getChar() >= 'A' && auxPorto[i]->getChar() <= 'Z') {
				
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::VERDE_CLARO);
				cout << char(254);
	}
			if (auxPorto[i]->getChar() >= 'a' && auxPorto[i]->getChar() <= 'z') {
				Consola::gotoxy(x, y);
				Consola::setTextColor(Consola::VERMELHO);
				cout << char(254);
			}


		Consola::gotoxy(x, y);
		cout << auxPorto[i]->getChar();
	}
}
void Interface::mostraNavios() {

	const vector <const Navios *>  auxNavio = mundo.getVetorNavios();

	for (unsigned int i = 0; i < auxNavio.size(); i++) {
		unsigned int x = auxNavio[i]->getX();
		unsigned int y = auxNavio[i]->getY();

		Consola::gotoxy(x, y);
		Consola::setTextColor(Consola::BRANCO_CLARO);
		Consola::gotoxy(x, y);
		cout << auxNavio[i]->getId();
	}
}
void Interface::mostraMapa() {

	mostraMar();
	mostraTerra();
	mostraPortos();
	mostraNavios();
	
	mostraLegAndConfig();
};


Interface::~Interface()
{
}
