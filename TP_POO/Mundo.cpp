#include "Mundo.h"
#include "Jogador.h"
using namespace std;
Mundo::Mundo() {

}

int Mundo::verificaCelula(int x, int y) {

	for (unsigned int i = 0; i < this->mar.size(); i++) {

		if (this->mar[i]->getX() == x && this->mar[i]->getY())
			return CELULA_MAR;
	}

	return 0;
}
int Mundo::moveNavio(int id,int direcao) {
	
	signed int x, y, ValidaMove = INVAL_MOVE;

	for (unsigned int i = 0; i < navios.size(); i++) {
		if (navios[i]->getId() == id) {
			switch (direcao) {
			
			case moveEsquerda:
				x = navios[i]->getX() - 1;
				//e ver se a nova pos está dentro de agua!
				if (x >= 0 && verificaCelula( x, navios[i]->getY()) == CELULA_MAR) {
					navios[i]->setX(x);
					ValidaMove = VAL_MOVE;
				}
				break;
			case moveDireita:
				x = navios[i]->getX() + 1;
				//e ver se a nova pos está dentro de agua!
				if (x < dimX && verificaCelula(x, navios[i]->getY()) == CELULA_MAR) {
					navios[i]->setX(x);
					ValidaMove = VAL_MOVE;
				}
				break;
			case moveCima:
				y = navios[i]->getY() - 1;
				//e ver se a nova pos está dentro de agua!
				if (y >= 0 && verificaCelula(navios[i]->getX(), y) == CELULA_MAR) {
					navios[i]->setY(y);
					ValidaMove = VAL_MOVE;
				}
				break;
			case moveBaixo:
				y = navios[i]->getY() + 1;
				//e ver se a nova pos está dentro de agua!
				if (y < dimY && verificaCelula(navios[i]->getX(), y) == CELULA_MAR) {
					navios[i]->setY(y);
					ValidaMove = VAL_MOVE;
				}
				break;
			}
		}
	}
	return ValidaMove;
}
Navios & Mundo::criaNavio(const char tipo) {

	int x, y;
	Navios *aux;
	for (unsigned int i = 0; i < porto.size(); i++) {

		if (porto[i]->getChar() == tipo) {

			x = porto[i]->getX();

			y = porto[i]->getY();
		}
	}
	aux = new Navios(tipo, x, y);
	
	this->navios.push_back(aux);

	return *aux;
}
const char Mundo::getPortoPrincipal() {

	for (unsigned int i = 0; i < porto.size(); i++) {

		if (porto[i]->getChar() >= 'A' && porto[i]->getChar() <= 'Z') {

			return porto[i]->getChar();

		}	
	}
	return '-';

}
void Mundo::criaCelulaMar(int x, int y)
{

	this->mar.push_back(new Mar(x,y));

}
void Mundo::criaCelulaTerra(int x, int y)
{

	this->terra.push_back(new Terra(x, y));

}
void Mundo::criaCelulaPorto(int x, int y,char t)
{

	this->porto.push_back(new Porto(x, y, t));

}
const vector<const Mar*> Mundo::getVetorMar() const
{
	return vector<const Mar *>(this->mar.begin(), this->mar.end());
}
const vector<const Terra*> Mundo::getVetorTerra() const
{
	return vector<const Terra *>(this->terra.begin(), this->terra.end());
}
const vector<const Porto*> Mundo::getVetorPorto() const
{
	return vector<const Porto *>(this->porto.begin(), this->porto.end());
}
const vector<const Navios*> Mundo::getVetorNavios() const
{
	return vector<const Navios *>(this->navios.begin(), this->navios.end());
}
bool Mundo::validaIdNavio(int idNavio) {


	for (unsigned int i = 0; i < navios.size(); i++) {

		if (navios[i]->getId() == idNavio) {
			//navios[i]->setAutoMove(true);
			return true;
		}

	}
	return false;

}
void Mundo::AlteraAutoMoveNavio(int idNavio, int autoMove) {

	for (unsigned int i = 0; i < navios.size(); i++) {
		if (navios[i]->getId() == idNavio) 
			navios[i]->setAutoMove(autoMove);
	}
}
bool Mundo::verificaModoAutomaticoNavio(int idNavio) {

	for (unsigned int i = 0; i < this->navios.size(); i++)
		if ( navios[i]->getId() == idNavio)
			if (navios[i]->getAutoMove() == AUTOMOVE_ON)
				return true;
	
	return false;
}
void Mundo::moveNavioAuto() {

	for (unsigned int i = 0; i < navios.size(); i++) {

		if (navios[i]->getAutoMove() == 1) {

			unsigned int direcao;

			direcao = rand() % 5 + 1;

			moveNavio(navios[i]->getId(), direcao);
		}
	}
}
void Mundo::setDimX(int xMax) {
	this->dimX = xMax;
}
void Mundo::setDimY(int yMax) {
	this->dimY = yMax;
}
const int Mundo::getDimX()const {
	return this->dimX;
}
const int Mundo::getDimY() const{
	return this->dimY;
}
Mundo::~Mundo()
{
}
