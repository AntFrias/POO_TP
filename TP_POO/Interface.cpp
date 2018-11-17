#include "Interface.h"

using namespace std;


Interface::Interface(){}

void Interface::mostraLegAndConfig() {

	Consola::gotoxy(25, 0);
	cout << "Legenda do Mapa";

	Consola::gotoxy(25, 2);
	cout << "\tMar -> .";

	Consola::gotoxy(25, 3);
	cout << "\tTerra -> +";

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
		cout << auxMar[i]->getChar();
	}

}
void Interface::mostraTerra() {

	const vector <const Terra *>  auxTerra = mundo.getVetorTerra();

	for (unsigned int i = 0; i < auxTerra.size(); i++) {
		unsigned int x = auxTerra[i]->getX();
		unsigned int y = auxTerra[i]->getY();

		Consola::gotoxy(x, y);
		cout << auxTerra[i]->getChar();
	}
}
void Interface::mostraPortos() {

	const vector <const Porto *>  auxPorto = mundo.getVetorPorto();

	for (unsigned int i = 0; i < auxPorto.size(); i++) {
		unsigned int x = auxPorto[i]->getX();
		unsigned int y = auxPorto[i]->getY();

		Consola::gotoxy(x, y);
		cout << auxPorto[i]->getChar();
	}
}

void Interface::start(){

	carregaFich();
	mostraMapa();

}
void Interface::mostraMapa() {

	mostraMar();
	mostraTerra();
	mostraPortos();
	mostraLegAndConfig();
};

void Interface::carregaFich() {
	
	fstream fp;

	int inteiro, contaLinhas = 0;
	string linha;

	if (!fp.is_open()) {
		fp.open(configInit);
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

}

Interface::~Interface()
{
}
