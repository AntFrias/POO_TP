#include "Navios.h"
#include "Mundo.h"

Navios::Navios()
{
}

//Navios::Navios(int preco,int tipo,int quantSoldados,int quantAgua){
//
//	this->id = ++this->IncNavio;
//	this->preco = preco;
//	this->tipo = tipo;
//	this->quantSoldados = quantSoldados;
//	this->quantAgua = quantAgua;
//}

Navios::Navios(Mundo *mundo, char tipo, int x, int y, int quantSoldados, int quantAgua, int autoMove)
{
	this->mundo = mundo;
	this->id = this->IncNavio++;
	this->tipo = tipo;
	this->quantAgua = quantAgua;
	this->quantSoldados = quantSoldados;
	this->autoMove = autoMove;
	this->x = x;
	this->y = y;
}
int Navios::moveNavio(int direcao) {

	switch (direcao) {

	case moveEsquerda:
		//e ver se a nova pos está dentro de agua!
		if (x > -1 && mundo->verificaCelulaMar(this->x - 1, this->y) == CELULA_MAR && mundo->verificaCelulaNavio(this->x - 1, this->y)!= CELULA_NAVIO ) {
			this->x = this->x - 1;
			return MOVE_VALIDO;
		}else
			if (x==0 && mundo->verificaCelulaMar(mundo->getDimX()-1, this->y) == CELULA_MAR && mundo->verificaCelulaNavio(mundo->getDimX()-1, this->y) != CELULA_NAVIO) {
				this->x = mundo->getDimX() - 1;
				return MOVE_VALIDO;
			}

		break;
	case moveDireita:
		//e ver se a nova pos está dentro de agua!
		if (x < mundo->getDimX() && mundo->verificaCelulaMar(this->x + 1, this->y) == CELULA_MAR && mundo->verificaCelulaNavio(this->x + 1, this->y) != CELULA_NAVIO) {
			this->x = this->x + 1;
			return MOVE_VALIDO;
		}
		else
			if (x == mundo->getDimX()-1 && mundo->verificaCelulaMar(0, this->y) == CELULA_MAR && mundo->verificaCelulaNavio(0, this->y) != CELULA_NAVIO) {
				this->x = 0;
				return MOVE_VALIDO;
			}
		break;
	case moveCima:
		//e ver se a nova pos está dentro de agua!
		if (y > 0 && mundo->verificaCelulaMar(this->x, this->y-1) == CELULA_MAR && mundo->verificaCelulaNavio(this->x, this->y-1) != CELULA_NAVIO) {
			this->y = this->y - 1;
			return MOVE_VALIDO;
		}
		else
			if (y == 0 && mundo->verificaCelulaMar(this->x, mundo->getDimY()-1 ) == CELULA_MAR && mundo->verificaCelulaNavio(this->x, mundo->getDimY()-1) != CELULA_NAVIO) {
				this->y = mundo->getDimY()-1;
				return MOVE_VALIDO;
			}
		break;
	case moveBaixo:
		//e ver se a nova pos está dentro de agua!
		if (y < mundo->getDimY() && mundo->verificaCelulaMar(this->x, this->y + 1) == CELULA_MAR && mundo->verificaCelulaNavio(this->x, this->y+1) != CELULA_NAVIO) {
			this->y = this->y + 1;
			return MOVE_VALIDO;
		}
		else
			if (y == mundo->getDimY()-1 && mundo->verificaCelulaMar(this->x, 0) == CELULA_MAR && mundo->verificaCelulaNavio(this->x, 0) != CELULA_NAVIO) {
				this->y = 0;
				return MOVE_VALIDO;
			}
		break;
	}
	return MOVE_INVALIDO;
}

int Navios::getX()const {
	
	return this->x;
}
int Navios::getY()const {

	return this->y;
}
void Navios::setX(int x) {

	this->x=x;
}
const int Navios::getId()const {
	return this->id;
}

const Navios Navios::getNavio() const
{
	return *this;
}

int Navios::getIncNavio() {
	return this->IncNavio;
}

void Navios::setY(int y) {

	this->y=y;
}
void Navios::setAutoMove(bool move) {
	this->autoMove = move;
}
int Navios::getAutoMove() {
	return this->autoMove;
}

Navios::~Navios()
{
}
