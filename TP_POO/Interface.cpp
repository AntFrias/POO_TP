#include "Interface.h"

using namespace std;


Interface::Interface(){}

int Interface::FiltaComandos(string acao) {

	vector< string > comandos = { "config", "exec","prox", "compranav", "vendenav", "lista", "compra", "vende", "move", "auto", "stop", "pirata","evpos","evnav",
								  "moedas","vaipara", "comprasold", "saveg", "loadg", "delg", "sair" };

	for (unsigned int i = 0; i < comandos.size(); i++) {
		if (comandos[i].compare(acao) == 0)
			return i + 1;
	}
	return 0;
}

void Interface::Prompt() {

	string linha, acao,configFile;
	int flag = 0;

	do {
		Consola::VERDE;
		Consola::gotoxy(0, 16);
		cout << "Comando: ";
		getline(cin, linha);

		istringstream buffer(linha);

		if (buffer >> acao) {

			switch (FiltaComandos(acao)) {

			case com_config:
				// falta testar os parametros
				
				if (buffer >> configFile and flag == 0) {

						flag=carregaFich(configFile);
						
						Consola::gotoxy(0, 16);
						
						if (flag == 0) {
							cout << "[ Ficheiro Passado pelo comando carregado com sucesso]" << endl;
						}
						else
							cout << "[ Ficheiro Passado pelo comando Nao existe  --- Ficheiro por default carregado com sucesso]" << endl;
				flag = 2;
				}else
					if(flag==1)
						cout << "[ SINTAXE DE COMANDO ERRADA -> config < Nome do Ficheiro > ]" << endl;
					else
						cout << "Configuraçoes já foram carregadas --- Introduza outro comando" << endl;
				break;
			case com_exec:
				cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
				break;
			case com_prox:
				cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
				break;
			case com_compranav:
				cout << "[ COMANDO : " << acao << " ainda nao Implementado ] " << endl;
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
				if (acao != "sair")
					cout << " [ ERRO ] Comando Incorreto..!" << endl;
			}
		}
		// validar quantidade de parametros e validar sem parametros
		// so config tb nao valida

		
		mostraMapa();
		Consola::getch();
		Consola::clrscr();
		mostraMapa();
	} while (linha != "sair");




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

void Interface::start(){


	Prompt();

	//carregaFich();
	//mostraMapa();

}
void Interface::mostraMapa() {

	mostraMar();
	mostraTerra();
	mostraPortos();
	mostraLegAndConfig();
};

int Interface::carregaFich(string configFile) {
	
	fstream fp;

	int inteiro, contaLinhas = 0,flag = 0;
	string linha;

	if (!fp.is_open()) {
		fp.open(configFile);
		if (!fp.is_open()) {
			fp.open(configInit);
			if (!fp.is_open()) {
				exit(-1);
			}
			flag = FICHEIROCONFIGERROR;
		}
	}
	
	

	while (getline(fp, linha)) {

		istringstream buffer(linha);

		if (buffer >> linha && buffer >> inteiro) {

			if (linha == "linhas")
				this->linhas = inteiro;
			else if (linha == "colunas")
				this->colunas = inteiro;
			else if (linha == "moedas")
				this->moedas = inteiro;
			else if (linha == "probpirata")
				this->probPirata = inteiro;
			else if (linha == "preconavio")
				this->precoNavio = inteiro;
			else if (linha == "precosoldado")
				this->precoSoldado = inteiro;
			else if (linha == "precovendpeixe")
				this->precoVendePeixe = inteiro;
			else if (linha == "precocompmercad")
				this->precoCompraMercadoria = inteiro;
			else if (linha == "precovendmercad")
				this->precoVendaMercadoria = inteiro;
			else if (linha == "soldadosporto")
				this->soldadosPorto = inteiro;
			else if (linha == "probevento")
				this->probVento = inteiro;
			else if (linha == "probtempestade")
				this->probTempestade = inteiro;
			else if (linha == "probsereias")
				this->probSereias = inteiro;
			else if (linha == "probcalmaria")
				this->probCalmaria = inteiro;
			else if (linha == "probmotin")
				this->probMotin = inteiro;
		}
		else {
			buffer >> linha;
			for (int i = 0; i < this->colunas; i++) {
				if (linha[i] == '.') {
					
					this->mundo.criaCelulaMar(i,contaLinhas);
				}
				if (linha[i] == '+') {

					this->mundo.criaCelulaTerra(i,contaLinhas);
				}
				if (linha[i] >= 'A' && linha[i] <= 'Z' || linha[i] >= 'a' && linha[i] <= 'z') {
					
					this->mundo.criaCelulaPorto(i,contaLinhas,linha[i]);

				}
			}
			contaLinhas++;
		}
	}
	fp.close();
	return flag;
}

Interface::~Interface()
{
}
