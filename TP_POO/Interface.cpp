#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>


#include "Interface.h"


#define configInit "configIni.txt"

using namespace std;


Interface::Interface(){}

void Interface::start(){

	carregaFich();
	mostraMapa();

}
void Interface::mostraMapa() {

	vector < Mar > aux = mundo.getVetorMar();
	
	for (unsigned int i = 0; i < aux.size(); i++) {
		int x = aux[i].getX();
		//int y = mar.getY();
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
					
					this->mundo.criaCelulaMar(contaLinhas,i);
				}
				if (linha[i] == '+') {

					this->mundo.criaCelulaTerra(contaLinhas, i);
				}
				if (linha[i] >= 'A' && linha[i] <= 'Z' || linha[i] >= 'a' && linha[i] <= 'z') {
					
					this->mundo.criaCelulaPorto(contaLinhas, i,linha[i]);

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
