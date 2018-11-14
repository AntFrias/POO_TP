#include "Mundo.h"

using namespace std;
Mundo::Mundo() {

};
Mundo::Mundo(int linhas, int colunas,
	int moedas,
	int probPirata,
	int precoNavio,
	int precoSoldado,
	int precoVendePeixe,
	int precoCompraMercadoria,
	int precoVendaMercadoria,
	int soldadosPorto,
	int probVento,
	int probTempestade,
	int probSereias,
	int probCalmaria,
	int probMotin,
	Mar &m,
	Terra &t,
	Porto &p
	) : mar(&m),terra(&t),porto(&p)
{
	this->moedas = moedas;
		this->probPirata = probPirata;
		this->precoNavio = precoNavio;
		this->precoSoldado = precoSoldado;
		this->precoVendePeixe = precoVendePeixe;
		this->precoCompraMercadoria = precoCompraMercadoria;
		this->precoVendaMercadoria = precoVendaMercadoria;
		this->soldadosPorto = soldadosPorto;
		this->probVento = probVento;
		this->probTempestade = probTempestade;
		this->probSereias = probSereias;
		this->probCalmaria = probCalmaria;
		this->probMotin = probMotin;


};


Mundo::~Mundo()
{
}
