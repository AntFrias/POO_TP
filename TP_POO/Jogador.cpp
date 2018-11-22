#include "Jogador.h"

Jogador::Jogador(){
}

void Jogador::setMoedas(int moedas) {

	this->moedas = moedas;

}

const int Jogador::getMoedas()const {

	return this->moedas;
	
}

bool Jogador::validaCompra(int valor) {

	if (this->moedas - valor >= 0) {
		return true;
	}
	else
		return false;

}
void Jogador::setPortoPrincipal(char tipo) {

	this->portoPrincipal = tipo;


}
const char Jogador::getPortoPrincipal() {

	return this->portoPrincipal;


}
void Jogador::addNavioJogador(Navios *navio) {

	this->navios.push_back(navio);
}
const vector<const Navios*> Jogador::getVetorNaviosJogador() const
{
	return vector<const Navios *>(this->navios.begin(), this->navios.end());
}

Jogador::~Jogador()
{
}
