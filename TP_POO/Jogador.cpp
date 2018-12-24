#include "Jogador.h"
#include "Mundo.h"

Jogador::Jogador(){
}

void Jogador::setMundo(Mundo *mundo){

	this->mundo = mundo;

}

void Jogador::setMoedas(int moedas) {

	this->moedas = moedas;

}

const int Jogador::getMoedas()const {

	return this->moedas;
	
}
int Jogador::vendeNavio(char tipo,int precoSoldado) {

	int dinheiroSoldados = 0;

	switch (tipo)
	{
	case 'F':

		for (unsigned int i = 0; i < navios.size(); i++) {
			if (navios[i]->sou() == FRAGATA && mundo->verificaCelulaPorto(navios[i]->getX(), navios[i]->getY()) == CELULA_PORTO_AMIGO) {
				dinheiroSoldados = navios[i]->getNumSoldados();
				//TODO VENDER PEIXE
				dinheiroSoldados *= precoSoldado;
				navios[i]->setEstado(afundado);
				return dinheiroSoldados + 100;//100 � o pre�o do navio
			}
		}
		
		//+ o do peixe
		break;
	case 'V':

		for (unsigned int i = 0; i < navios.size(); i++) {
			if (navios[i]->sou() == VELEIRO && mundo->verificaCelulaPorto(navios[i]->getX(), navios[i]->getY()) == CELULA_PORTO_AMIGO) {
				dinheiroSoldados = navios[i]->getNumSoldados();
				//TODO VENDER PEIXE
				dinheiroSoldados *= precoSoldado;
				navios[i]->setEstado(afundado);
				return dinheiroSoldados + 100;//100 � o pre�o do navio
			}
		}

		break;
	case 'G':

		for (unsigned int i = 0; i < navios.size(); i++) {
			if (navios[i]->sou() == GALEAO && mundo->verificaCelulaPorto(navios[i]->getX(), navios[i]->getY()) == CELULA_PORTO_AMIGO) {
				dinheiroSoldados = navios[i]->getNumSoldados();
				//TODO VENDER PEIXE
				dinheiroSoldados *= precoSoldado;
				navios[i]->setEstado(afundado);
				return dinheiroSoldados + 100;//100 � o pre�o do navio
			}
		}

		break;
	case 'E':

		for (unsigned int i = 0; i < navios.size(); i++) {
			if (navios[i]->sou() == ESCUNA && mundo->verificaCelulaPorto(navios[i]->getX(), navios[i]->getY()) == CELULA_PORTO_AMIGO) {
				dinheiroSoldados = navios[i]->getNumSoldados();
				//TODO VENDER PEIXE
				dinheiroSoldados *= precoSoldado;
				navios[i]->setEstado(afundado);
				return dinheiroSoldados + 100;//100 � o pre�o do navio
			}
		}

		break;
	default:
		break;
	}
	return 0;
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
string Jogador::moveNavioAuto() {
	
	ostringstream os;

	for (unsigned int i = 0; i < navios.size(); i++) {

		if (navios[i]->getEstado() == autoMove || navios[i]->getEstado() == aDeriva) {

			unsigned int direcao;

			direcao = rand() % 9 + 1;

			this->navios[i]->moveNavio(direcao);
			if (navios[i]->getEstado()==autoMove) {
				this->navios[i]->soldadosBebemAgua();
				os<<this->navios[i]->combate(CELULA_NAVIO_PIRATA);
			}
		}
	}
	return os.str();
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
