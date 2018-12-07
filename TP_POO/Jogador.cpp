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

			if (navios[i]->getAutoMove() == AUTOMOVE_ON)
				return true;
		}
		
	}
	return false;
}
void Jogador::moveNavioAuto() {

	for (unsigned int i = 0; i < navios.size(); i++) {

		if (navios[i]->getAutoMove() == 1) {

			unsigned int direcao;

			direcao = rand() % 5 + 1;

			this->navios[i]->moveNavio(direcao);
		}
	}
}
int Jogador::moveNavioJogador(int id, int direcao) {

	signed int ValidaMove = INVAL_MOVE;

	for (unsigned int i = 0; i < navios.size(); i++) {
		if (navios[i]->getId() == id)
			ValidaMove = navios[i]->moveNavio(direcao);
		
	}
	return ValidaMove;
}
bool Jogador::validaIdNavio(int idNavio) {


	for (unsigned int i = 0; i < navios.size(); i++) {

		if (navios[i]->getId() == idNavio) {
			//navios[i]->setAutoMove(true);
			return true;
		}

	}
	return false;

}
void Jogador::AlteraAutoMoveNavio(int idNavio, int autoMove) {

	for (unsigned int i = 0; i < navios.size(); i++) {
		if (navios[i]->getId() == idNavio)
			navios[i]->setAutoMove(autoMove);
	}
}
const vector<const Navios*> Jogador::getVetorNaviosJogador() const
{
	return vector<const Navios *>(this->navios.begin(), this->navios.end());
}

Jogador::~Jogador()
{
}
