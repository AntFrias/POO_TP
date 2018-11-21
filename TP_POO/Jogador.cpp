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


}void Jogador::CriaNavioJogador(Navios &navio) {

	this->navios.push_back(&navio);

}

Jogador::~Jogador()
{
}
