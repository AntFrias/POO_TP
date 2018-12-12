#include "Navios.h"
#include "Mundo.h"

Navios::Navios()
{
}

Navios::Navios(Mundo *mundo, char tipo, int x, int y, int quantSoldados, int quantAgua, bool autoMove, bool atracado)
{
	this->mundo = mundo;
	this->id = this->IncNavio++;
	this->tipo = tipo;
	this->quantAgua = quantAgua;
	this->quantSoldados = quantSoldados;
	this->autoMove = autoMove;
	this->Atracado = atracado;
	this->x = x;
	this->y = y;
}
int Navios::moveNavio(int direcao) {
	int VerificaPorto;
	switch (direcao) {

	case moveEsquerda:
		//e ver se a nova pos está dentro de agua!
		if (x > 0 && (mundo->verificaCelulaMar(this->x - 1, this->y) == CELULA_MAR)){
			VerificaPorto = mundo->verificaCelulaPorto(this->x - 1, this->y);
			if (VerificaPorto == CELULA_PORTO_AMIGO) {
				this->x = this->x - 1;
				return MOVE_VALIDO;
			}
			if (VerificaPorto == CELULA_SEM_PORTO) {
				if (mundo->verificaCelulaNavio(this->x - 1, this->y) != CELULA_NAVIO) {
					this->x = this->x - 1;
					return MOVE_VALIDO;
				} else {
					return MOVE_INVALIDO;

				}
			}
			if (VerificaPorto == CELULA_PORTO_INIMIGO)
				return MOVE_INVALIDO;	
		}
		else
			if (x == 0 &&
				(mundo->verificaCelulaMar(mundo->getDimX() - 1, this->y) == CELULA_MAR &&
					mundo->verificaCelulaPorto(mundo->getDimX() - 1, this->y) != CELULA_PORTO_INIMIGO) &&
				mundo->verificaCelulaNavio(mundo->getDimX() - 1, this->y) != CELULA_NAVIO) {
				this->x = mundo->getDimX() - 1;
				return MOVE_VALIDO;
			}

		break;
	case moveDireita:
		//e ver se a nova pos está dentro de agua!
		if (x < mundo->getDimX()-1 &&
			(mundo->verificaCelulaMar(this->x + 1, this->y) == CELULA_MAR &&
				mundo->verificaCelulaPorto(this->x + 1, this->y) != CELULA_PORTO_INIMIGO) &&
			mundo->verificaCelulaNavio(this->x + 1, this->y) != CELULA_NAVIO) {
			

		/*	if (mundo->verificaCelulaMar(this->x + 1, this->y) == CELULA_MAR)
				cout << "Sou mar\n"<< " x " <<this->x+1 << "y"<< this->y;
				cout << "Sou : \n" << mundo->verificaCelulaPorto(this->x + 1, this->y);
			if (mundo->verificaCelulaNavio(this->x + 1, this->y) != CELULA_NAVIO)
				cout << "Não sou um navio\n";
				
				*/
			this->x = this->x + 1;


			return MOVE_VALIDO;
		}
		else
			if (x == mundo->getDimX() - 1 &&
				(mundo->verificaCelulaMar(0, this->y) == CELULA_MAR &&
					mundo->verificaCelulaPorto(0, this->y) != CELULA_PORTO_INIMIGO) &&
				mundo->verificaCelulaNavio(0, this->y) != CELULA_NAVIO) {
				this->x = 0;
				return MOVE_VALIDO;
			}
		break;
	case moveCima:
		//e ver se a nova pos está dentro de agua!
		if (y > 0 &&
			(mundo->verificaCelulaMar(this->x, this->y - 1) == CELULA_MAR &&
				mundo->verificaCelulaPorto(this->x, this->y - 1) != CELULA_PORTO_INIMIGO) &&
			mundo->verificaCelulaNavio(this->x, this->y - 1) != CELULA_NAVIO) {
			this->y = this->y - 1;
			return MOVE_VALIDO;
		}
		else
			if (y == 0 &&
				(mundo->verificaCelulaMar(this->x, mundo->getDimY() - 1) == CELULA_MAR &&
					mundo->verificaCelulaPorto(this->x, mundo->getDimY() - 1) != CELULA_PORTO_INIMIGO) &&
				mundo->verificaCelulaNavio(this->x, mundo->getDimY() - 1) != CELULA_NAVIO) {
				this->y = mundo->getDimY() - 1;
				return MOVE_VALIDO;
			}
		break;
	case moveBaixo:
		//e ver se a nova pos está dentro de agua!
		if (y < mundo->getDimY() - 1 &&
			(mundo->verificaCelulaMar(this->x, this->y + 1) == CELULA_MAR &&
				mundo->verificaCelulaPorto(this->x, this->y + 1) != CELULA_PORTO_INIMIGO) &&
			mundo->verificaCelulaNavio(this->x, this->y + 1) != CELULA_NAVIO) {
			this->y = this->y + 1;
			return MOVE_VALIDO;
		}
		else
			if (y == mundo->getDimY() - 1 &&
				(mundo->verificaCelulaMar(this->x, 0) == CELULA_MAR &&
					mundo->verificaCelulaPorto(this->x, 0) != CELULA_PORTO_INIMIGO) &&
				mundo->verificaCelulaNavio(this->x, 0) != CELULA_NAVIO) {
				this->y = 0;
				return MOVE_VALIDO;
			}
		break;
	case moveCimaEsquerda:
		//anda normal
		if ((y > 0 && y <= mundo->getDimY() - 1) && (x > 0 && x <= mundo->getDimX() - 1) &&
			(mundo->verificaCelulaMar(this->x - 1, this->y - 1) == CELULA_MAR &&
				mundo->verificaCelulaPorto(this->x - 1, this->y - 1) != CELULA_PORTO_INIMIGO) &&
			mundo->verificaCelulaNavio(this->x - 1, this->y - 1) != CELULA_NAVIO) {
			this->y = this->y - 1;
			this->x = this->x - 1;
			return MOVE_VALIDO;
		}
		////encostado a cima
		if ((y == 0 && (x > 0 && x <= mundo->getDimX() - 1)) &&
			(mundo->verificaCelulaMar(this->x - 1, mundo->getDimY() - 1) == CELULA_MAR &&
				mundo->verificaCelulaPorto(this->x - 1, mundo->getDimY() - 1) != CELULA_PORTO_INIMIGO) &&
			mundo->verificaCelulaNavio(this->x - 1, mundo->getDimY() - 1) != CELULA_NAVIO) {
			this->x = this->x - 1;
			this->y = mundo->getDimY() - 1;
			return MOVE_VALIDO;
		}
		////encostado à esquerda
		if ((x == 0 && (y > 0 && y <= mundo->getDimY() - 1)) &&
			(mundo->verificaCelulaMar(mundo->getDimX() - 1, this->y - 1) == CELULA_MAR &&
				mundo->verificaCelulaPorto(mundo->getDimX() - 1, this->y - 1) != CELULA_PORTO_INIMIGO) &&
			mundo->verificaCelulaNavio(mundo->getDimX() - 1, this->y - 1) != CELULA_NAVIO) {
			this->x = mundo->getDimX() - 1;
			this->y = this->y - 1;
			return MOVE_VALIDO;
		}
		//canto superior esquerdo
		if ((y == 0 && x == 0) &&
			(mundo->verificaCelulaMar(mundo->getDimX() - 1, mundo->getDimY() - 1) == CELULA_MAR &&
				mundo->verificaCelulaPorto(mundo->getDimX() - 1, mundo->getDimY() - 1) != CELULA_PORTO_INIMIGO) &&
			mundo->verificaCelulaNavio(mundo->getDimX() - 1, mundo->getDimY() - 1) != CELULA_NAVIO) {
			this->x = mundo->getDimX() - 1;
			this->y = mundo->getDimY() - 1;
			return MOVE_VALIDO;
		}
		break;
	case moveCimaDireita:

		//anda normal
		if (y > 0 && y <= mundo->getDimY()-1 && x > 0 && x < mundo->getDimX() - 1 &&
			(mundo->verificaCelulaMar(this->x + 1, this->y - 1) == CELULA_MAR &&
				mundo->verificaCelulaPorto(this->x + 1, this->y - 1) != CELULA_PORTO_INIMIGO) &&
			mundo->verificaCelulaNavio(this->x + 1, this->y - 1) != CELULA_NAVIO) {

			this->y = this->y - 1;
			this->x = this->x + 1;
			return MOVE_VALIDO;
		}
		//encostado a cima
		if ((y == 0 && (x>=0 && x < mundo->getDimX() - 1)) &&
			(mundo->verificaCelulaMar(this->x + 1, mundo->getDimY() - 1) == CELULA_MAR &&
				mundo->verificaCelulaPorto(this->x + 1, mundo->getDimY() - 1) != CELULA_PORTO_INIMIGO) &&
			mundo->verificaCelulaNavio(this->x + 1, mundo->getDimY() - 1) != CELULA_NAVIO) {
			this->x = this->x + 1;
			this->y = mundo->getDimY() - 1;
			
			return MOVE_VALIDO;
		}
		//encostado à direita
		if ((x == mundo->getDimX() - 1 && y > 0 && y <= mundo->getDimY() - 1) &&
			(mundo->verificaCelulaMar(0, this->y - 1) == CELULA_MAR &&
				mundo->verificaCelulaPorto(0, this->y - 1) != CELULA_PORTO_INIMIGO) &&
			mundo->verificaCelulaNavio(0, this->y - 1) != CELULA_NAVIO) {
			this->x = 0;
			this->y = this->y - 1;
			return MOVE_VALIDO;
		}
		//canto superior direito
		if (y == 0 && x == mundo->getDimX() - 1 &&
			(mundo->verificaCelulaMar(0, mundo->getDimY() - 1) == CELULA_MAR &&
				mundo->verificaCelulaPorto(0, mundo->getDimY() - 1) != CELULA_PORTO_INIMIGO) &&
			mundo->verificaCelulaNavio(0, mundo->getDimY() - 1) != CELULA_NAVIO) {

			
			this->x = 0;
			this->y = mundo->getDimY() - 1;
			
			return MOVE_VALIDO;
		}

		break;
	case moveBaixoEsquerda:
		//anda normal
		if ((y >= 0 && y < mundo->getDimY()-1)&& ( x > 0 && x <= mundo->getDimX() - 1) &&
			(mundo->verificaCelulaMar(this->x - 1, this->y + 1) == CELULA_MAR &&
				mundo->verificaCelulaPorto(this->x - 1, this->y + 1) != CELULA_PORTO_INIMIGO) &&
			mundo->verificaCelulaNavio(this->x - 1, this->y + 1) != CELULA_NAVIO) {
			this->y = this->y + 1;
			this->x = this->x - 1;
			return MOVE_VALIDO;
		}
		//////encostado a baixo
		if ((y == mundo->getDimY() - 1) && (x > 0 && x <= mundo->getDimX() - 1) &&
			(mundo->verificaCelulaMar(this->x - 1, 0) == CELULA_MAR &&
				mundo->verificaCelulaPorto(this->x - 1, 0) != CELULA_PORTO_INIMIGO) &&
			mundo->verificaCelulaNavio(this->x - 1, 0) != CELULA_NAVIO) {
			this->x = this->x - 1;
			this->y = 0;
			return MOVE_VALIDO;
		}
		//////encostado à esquerda
		if ((x == 0) && (y >= 0 && y < mundo->getDimY() - 1) &&
			(mundo->verificaCelulaMar(mundo->getDimX() - 1, this->y + 1) == CELULA_MAR &&
				mundo->verificaCelulaPorto(mundo->getDimX() - 1, this->y + 1) != CELULA_PORTO_INIMIGO) &&
			mundo->verificaCelulaNavio(mundo->getDimX() - 1, this->y + 1) != CELULA_NAVIO) {
			this->x = mundo->getDimX() - 1;
			this->y = this->y + 1;
			return MOVE_VALIDO;
		}
		//canto inferior esquerdo
		if ((y == mundo->getDimY() - 1 && x == 0) &&
			(mundo->verificaCelulaMar(mundo->getDimX() - 1, 0) == CELULA_MAR &&
				mundo->verificaCelulaPorto(mundo->getDimX() - 1, 0) != CELULA_PORTO_INIMIGO) &&
			mundo->verificaCelulaNavio(mundo->getDimX() - 1, 0) != CELULA_NAVIO) {
			this->x = mundo->getDimX() - 1;
			this->y = 0;
			return MOVE_VALIDO;
		}

		break;
	case moveBaixoDireita:
		//anda normal
		if ((y >= 0 && y < mundo->getDimY()-1) && (x >= 0 && x < mundo->getDimX() - 1) &&
			(mundo->verificaCelulaMar(this->x + 1, this->y + 1) == CELULA_MAR &&
				mundo->verificaCelulaPorto(this->x + 1, this->y + 1) != CELULA_PORTO_INIMIGO) &&
			mundo->verificaCelulaNavio(this->x + 1, this->y + 1) != CELULA_NAVIO) {
			this->y = this->y + 1;
			this->x = this->x + 1;
			return MOVE_VALIDO;
		}
		////////encostado a baixo
		if ((y == mundo->getDimY() - 1) && (x >= 0 && x < mundo->getDimX() - 1) &&
			(mundo->verificaCelulaMar(this->x + 1, 0) == CELULA_MAR &&
				mundo->verificaCelulaPorto(this->x + 1, 0) != CELULA_PORTO_INIMIGO) &&
			mundo->verificaCelulaNavio(this->x + 1, 0) != CELULA_NAVIO) {
			this->x = this->x + 1;
			this->y = 0;
			return MOVE_VALIDO;
		}
		////////encostado à direita
		if ((x == mundo->getDimX() - 1) && (y >= 0 && y < mundo->getDimY() - 1) &&
			(mundo->verificaCelulaMar(0, this->y + 1) == CELULA_MAR &&
				mundo->verificaCelulaPorto(0, this->y + 1) != CELULA_PORTO_INIMIGO) &&
			mundo->verificaCelulaNavio(0, this->y + 1) != CELULA_NAVIO) {
			this->x = 0;
			this->y = this->y + 1;
			return MOVE_VALIDO;
		}
		////canto inferior esquerdo
		if ((y == mundo->getDimY() - 1 && x == mundo->getDimX() - 1) &&
			(mundo->verificaCelulaMar(0, 0) == CELULA_MAR &&
				mundo->verificaCelulaPorto(0, 0) != CELULA_PORTO_INIMIGO) &&
			mundo->verificaCelulaNavio(0, 0) != CELULA_NAVIO) {
			this->x = 0;
			this->y = 0;
			return MOVE_VALIDO;
		}

		break;
	}
	return MOVE_INVALIDO;
}
char Navios::getTipo() const
{
	return this->tipo;
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

const Navios * Navios::getNavio() const
{
	return this;
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

bool Navios::getNavioAtracado()
{
	return this->Atracado;
}

void Navios::setNavioAtracado(bool estado)
{
	this->Atracado = estado;
}

Navios::~Navios()
{
}
