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
bool Jogador::verificaModoAutomaticoNavio(int idNavio) {

	for (unsigned int i = 0; i < navios.size(); i++) {
		if (navios[i]->getId() == idNavio) {

			if (navios[i]->getEstado() == autoMove)
				return true;
		}
		
	}
	return false;
}
bool Jogador::verificaNaviosJogador() {

	if (navios.size() == 0) {
		return false;
	}
	return true;

}
void Jogador::moveNavioAuto() {

	for (unsigned int i = 0; i < navios.size(); i++) {

		if (navios[i]->getEstado() == autoMove || navios[i]->getEstado() == aDeriva) {

			unsigned int direcao;

			direcao = rand() % 9 + 1;

			this->navios[i]->moveNavio(direcao);
			if (navios[i]->getEstado()==autoMove) {
				this->navios[i]->soldadosBebemAgua();
				this->navios[i]->combate(CELULA_NAVIO_PIRATA);
			}
		}
	}
}
int Jogador::moveNavioJogador(int id, int direcao) {

	signed int ValidaMove = MOVE_INVALIDO;

	for (unsigned int i = 0; i < navios.size(); i++) {
		if (navios[i]->getId() == id)
			ValidaMove = navios[i]->moveNavio(direcao);
		
	}
	return ValidaMove;
}
bool Jogador::validaIdNavio(int idNavio) {


	for (unsigned int i = 0; i < navios.size(); i++) {

		if (navios[i]->getId() == idNavio) {
			return true;
		}

	}
	return false;

}
void Jogador::AlteraAutoMoveNavio(int idNavio, int estado) {

	for (unsigned int i = 0; i < navios.size(); i++) {
		if (navios[i]->getId() == idNavio)
			navios[i]->setEstado(estado);
	}
}
const vector<const Navios*> Jogador::getVetorNaviosJogador() const
{
	return vector<const Navios *>(this->navios.begin(), this->navios.end());
}

Jogador::~Jogador()
{
}
