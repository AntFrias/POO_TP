#include "Interface.h"

using namespace std;


Interface::Interface(){}

void Interface::start(){

	carregaFich();
	mostraMapa();

}
void Interface::mostraMapa() {

	const vector <const Mar *>  auxMar = mundo.getVetorMar();
	const vector <const Terra *>  auxTerra = mundo.getVetorTerra();
	const vector <const Porto *>  auxPorto = mundo.getVetorPorto();
	
	for (unsigned int i = 0; i < auxMar.size(); i++) {
		unsigned int x = auxMar[i]->getX();
		unsigned int y = auxMar[i]->getY();

		Consola::gotoxy(x, y);
		cout << auxMar[i]->getChar();
	}
	for (unsigned int i = 0; i < auxTerra.size(); i++) {
		unsigned int x = auxTerra[i]->getX();
		unsigned int y = auxTerra[i]->getY();

		Consola::gotoxy(x, y);
		cout << auxTerra[i]->getChar();
	}
	for (unsigned int i = 0; i < auxPorto.size(); i++) {
		unsigned int x = auxPorto[i]->getX();
		unsigned int y = auxPorto[i]->getY();

		Consola::gotoxy(x, y);
		cout << auxPorto[i]->getChar();
	}
}
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
			else if (linha == "probPirata")
				this->probPirata = inteiro;
			else if (linha == "precoNavio")
				this->precoNavio = inteiro;
			else if (linha == "precoSoldado")
				this->precoSoldado = inteiro;
			else if (linha == "precoVendePeixe")
				this->precoVendePeixe = inteiro;
			else if (linha == "precoCompraMercadoria")
				this->precoCompraMercadoria = inteiro;
			else if (linha == "precoVendaMercadoria")
				this->precoVendaMercadoria = inteiro;
			else if (linha == "soldadosPorto")
				this->soldadosPorto = inteiro;
			else if (linha == "probVento")
				this->probVento = inteiro;
			else if (linha == "probTempestade")
				this->probTempestade = inteiro;
			else if (linha == "probSereias")
				this->probSereias = inteiro;
			else if (linha == "probCalmaria")
				this->probCalmaria = inteiro;
			else if (linha == "probMotin")
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
