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
void Jogador::adicionaMoedas(int moedas)
{
	this->moedas = this->moedas + moedas;
}
Navios * Jogador::getNavio(int id) {

	for (unsigned int i = 0; i < navios.size(); i++)
		if (navios[i]->getId() == id)
			return navios[i];

	return nullptr;
}

Navios * Jogador::getNavioJogador(int id) {

	for (unsigned int i = 0; i < navios.size(); i++)
		if (navios[i]->getId() == id && navios[i]->getEstado() == normal || navios[i]->getEstado() == autoMove)
			return navios[i];

	return nullptr;
}
void Jogador::mandaVaiPara() {
	//cout << "meu x " << navios[i]->getX() << "meu y " << navios[i]->getY() << " xVaiPara " << navios[i]->getXvaiPara()<< " yVaiPara " << navios[i]->getYvaiPara() << endl;
	for (unsigned int i = 0; i < navios.size(); i++) {

		if (navios[i]->getEstado() == vaiPara) {

			if (navios[i]->getXvaiPara() < navios[i]->getX()) {
				if (navios[i]->moveNavio(moveEsquerda) == MOVE_VALIDO) {
					navios[i]->soldadosBebemAgua();
					cout << navios[i]->combate(CELULA_NAVIO_PIRATA);
				}
				else {
					navios[i]->moveNavio(rand() % 9 + 1);
					navios[i]->soldadosBebemAgua();
					cout << navios[i]->combate(CELULA_NAVIO_PIRATA);
				}

			}
			else
				if (navios[i]->getXvaiPara() > navios[i]->getX()) {
					if (navios[i]->moveNavio(moveDireita) == MOVE_VALIDO) {
						navios[i]->soldadosBebemAgua();
						cout << navios[i]->combate(CELULA_NAVIO_PIRATA);
					}
					else {
						navios[i]->moveNavio(rand() % 9 + 1);
						navios[i]->soldadosBebemAgua();
						cout << navios[i]->combate(CELULA_NAVIO_PIRATA);
					}
				}
				else
					if (navios[i]->getYvaiPara() < navios[i]->getY()) {
						if (navios[i]->moveNavio(moveCima) == MOVE_VALIDO) {
							navios[i]->soldadosBebemAgua();
							cout << navios[i]->combate(CELULA_NAVIO_PIRATA);
						}
						else {
							navios[i]->moveNavio(rand() % 9 + 1);
							navios[i]->soldadosBebemAgua();
							cout << navios[i]->combate(CELULA_NAVIO_PIRATA);
						}
					}
					else
						if (navios[i]->getYvaiPara() > navios[i]->getY()) {
							if (navios[i]->moveNavio(moveBaixo) == MOVE_VALIDO) {
								navios[i]->soldadosBebemAgua();
								cout << navios[i]->combate(CELULA_NAVIO_PIRATA);
							}
							else {
								navios[i]->moveNavio(rand() % 9 + 1);
								navios[i]->soldadosBebemAgua();
								cout << navios[i]->combate(CELULA_NAVIO_PIRATA);
							}
						}

			if ((navios[i]->getX() == navios[i]->getXvaiPara()) && (navios[i]->getY() == navios[i]->getYvaiPara()))
				navios[i]->setEstado(normal);

		}


	}




}
void Jogador::setVaiPara(int idNavio, int xVaiPara, int yVaiPara) {

	Navios *navioVaiPara = nullptr;
	navioVaiPara = getNavio(idNavio);

	if (navioVaiPara != nullptr && navioVaiPara->getEstado() != pirata) {
		if ((xVaiPara >= 0 && xVaiPara < mundo->getDimX()) && (yVaiPara >= 0 && yVaiPara < mundo->getDimY())) {

			navioVaiPara->setXvaiPara(xVaiPara);
			navioVaiPara->setYvaiPara(yVaiPara);
			navioVaiPara->setEstado(vaiPara);

		}
	}


}
void Jogador::setVaiPara(int idNavio, char tipo) {

	Navios *navioVaiPara = nullptr;
	Porto *portoDestino = nullptr;

	navioVaiPara = getNavio(idNavio);
	portoDestino = mundo->getPorto(tipo);

	if (navioVaiPara != nullptr && navioVaiPara->getEstado() != pirata) {
		// vai buscar as coodenadas do porto

		navioVaiPara->setXvaiPara(portoDestino->getX());
		navioVaiPara->setYvaiPara(portoDestino->getY());
		navioVaiPara->setEstado(vaiPara);


	}


}


int Jogador::vendeNavio(char tipo,int precoSoldado) {

	int dinheiroSoldados = 0;
	  //
	switch (tipo)
	{
	case 'F':

		for (unsigned int i = 0; i < navios.size(); i++) {
			if (navios[i]->getTipo() == 'F' ){
				if (mundo->verificaCelulaPorto(navios[i]->getX(), navios[i]->getY()) == CELULA_PORTO_AMIGO) {
					dinheiroSoldados = navios[i]->getNumSoldados();
					//TODO VENDER PEIXE
					dinheiroSoldados *= precoSoldado;
					navios[i]->setEstado(afundado);
					return dinheiroSoldados + 100;//100 � o pre�o do navio
				}
			}
		}
		
		//+ o do peixe
		break;
	case 'V':

		for (unsigned int i = 0; i < navios.size(); i++) {
			if (navios[i]->getTipo() == 'V') {
				if (mundo->verificaCelulaPorto(navios[i]->getX(), navios[i]->getY()) == CELULA_PORTO_AMIGO) {
					dinheiroSoldados = navios[i]->getNumSoldados();
					//TODO VENDER PEIXE
					dinheiroSoldados *= precoSoldado;
					navios[i]->setEstado(afundado);
					return dinheiroSoldados + 100;//100 � o pre�o do navio
				}
			}
		}

		break;
	case 'G':

		for (unsigned int i = 0; i < navios.size(); i++) {
			if (navios[i]->sou() == 'G') {
				if (mundo->verificaCelulaPorto(navios[i]->getX(), navios[i]->getY()) == CELULA_PORTO_AMIGO) {
					dinheiroSoldados = navios[i]->getNumSoldados();
					//TODO VENDER PEIXE
					dinheiroSoldados *= precoSoldado;
					navios[i]->setEstado(afundado);
					return dinheiroSoldados + 100;//100 � o pre�o do navio
				}
			}
		}

		break;
	case 'E':

		for (unsigned int i = 0; i < navios.size(); i++) {
			if (navios[i]->sou() == 'E') {
				if (mundo->verificaCelulaPorto(navios[i]->getX(), navios[i]->getY()) == CELULA_PORTO_AMIGO) {
					dinheiroSoldados = navios[i]->getNumSoldados();
					//TODO VENDER PEIXE
					dinheiroSoldados *= precoSoldado;
					navios[i]->setEstado(afundado);
					return dinheiroSoldados + 100;//100 � o pre�o do navio
				}
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
string Jogador::moveNavioAuto( int turnoAtual) {
	
	ostringstream os;

	for (unsigned int i = 0; i < navios.size(); i++) {

		if (navios[i]->getEstado()==autoMove || navios[i]->getEstado() == aDeriva) {
			os << navios[i]->moveNavioAuto(turnoAtual);
		}
	}
	return os.str();
}
int Jogador::moveNavioJogador(int id, int direcao, int turnoJogo) {

	signed int ValidaMove = MOVE_INVALIDO;

	for (unsigned int i = 0; i < navios.size(); i++) {
		if (navios[i]->getId() == id)
			ValidaMove = navios[i]->moveNavio(direcao, turnoJogo);
		
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
