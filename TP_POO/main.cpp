#include <iostream>
#include "funcoes.h"
#include "Mundo.h"
#include "Mar.h"
#include "Terra.h"
#include "Porto.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "funcoes.h"
#include <vector>
#include <sstream>
#include <string>

#define configInit "configIni.txt"



using namespace std;

Mundo carregaMundo(Mundo &mundo) {

	Mundo mundo;

	fstream fp;

	int inteiro, contaLinhas = 0;
	string linha;

	//Variaveis configuraçao inicial
	int nLinhas, nColunas;
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

	if (!fp.is_open()) {
		fp.open(configInit);
	}

	while (getline(fp, linha)) {

		istringstream buffer(linha);



		if (buffer >> linha && buffer >> inteiro) {

			if (linha == "linhas")
				nLinhas = inteiro;
			else if (linha == "colunas")
				nColunas = inteiro;
			else if (linha == "moedas")
				moedas = inteiro;
			else if (linha == "probPirata")
				probPirata = inteiro;
			else if (linha == "precoNavio")
				precoNavio = inteiro;
			else if (linha == "precoSoldado")
				precoSoldado = inteiro;
			else if (linha == "precoVendePeixe")
				precoVendePeixe = inteiro;
			else if (linha == "precoCompraMercadoria")
				precoCompraMercadoria = inteiro;
			else if (linha == "precoVendaMercadoria")
				precoVendaMercadoria = inteiro;
			else if (linha == "soldadosPorto")
				soldadosPorto = inteiro;
			else if (linha == "probVento")
				probVento = inteiro;
			else if (linha == "probTempestade")
				probTempestade = inteiro;
			else if (linha == "probSereias")
				probSereias = inteiro;
			else if (linha == "probCalmaria")
				probCalmaria = inteiro;
			else if (linha == "probMotin")
				probMotin = inteiro;
		}
		else {
			buffer >> linha;
			for (int i = 0; i < nColunas; i++) {
				if (linha[i] == '.') {
					Mar auxM(contaLinhas, i, linha[i]);

					mar.push_back(auxM);
				}
				if (linha[i] == '+') {
					Terra auxT(contaLinhas, i, linha[i]);

					terra.push_back(auxT);
				}
				if (linha[i] >= 'A' && linha[i] <= 'Z' || linha[i] >= 'a' && linha[i] <= 'z') {
					Porto auxP(contaLinhas, i, linha[i]);

					porto.push_back(auxP);
				}
			}
			contaLinhas++;
		}
	}
	fp.close();

	/*mundo(nLinhas,nColunas,
		moedas,
		probPirata,
		precoNavio,
		precoSoldado,
		precoVendePeixe,
		precoCompraMercadoria,
		precoVendaMercadoria,
		soldadosPorto,
		probVento,
		probTempestade,
		probSereias,
		probCalmaria,
		probMotin, &mar[0], &terra[0], &porto[0]);*/




	return mundo;

}





int main() {

	Mundo mundo;

	vector <Mar> mar;
	vector <Terra> terra;
	vector <Porto> porto;
	
	carregaMundo(mundo);

	for (unsigned int i=0; i < terra.size(); i++) {

		cout << "carater: " << terra[i].getT() << "\tx: " << terra[i].getX() << "\ty: " << terra[i].getY() << endl;

	}



	cin.get();
	return 0;
}