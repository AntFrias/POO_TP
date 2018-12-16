#include "Navios.h"
#include "Mundo.h"

Navios::Navios()
{
}

Navios::Navios(Mundo *mundo, char tipo, int x, int y, int quantSoldados, int quantAgua, bool autoMove, bool atracado,bool afundado)
{
	this->mundo = mundo;
	this->id = this->IncNavio++;
	this->tipo = tipo;
	this->quantAgua = quantAgua;
	this->quantSoldados = quantSoldados;
	this->autoMove = autoMove;
	this->Atracado = atracado;
	this->afundado = false;
	this->x = x;
	this->y = y;
}
int Navios::randNumber(int nSoldados) {

	if (nSoldados > 0) {
		return rand() % nSoldados + 1;
	}
	return 0;
}
void Navios::setAfundado(bool result) {

	this->afundado = result;
}
bool Navios::getAfundado() {

	return this->afundado;
}
void Navios::acao(int xaAtacar,int yaAtacar) {

	Navios *navioaAtacar=nullptr;
	navioaAtacar = mundo->getNavioXY(xaAtacar, yaAtacar);
	int randThis = 0, randNavioaAtacar = 0, soldadosPerdidos = 0;

	randThis = randNumber(this->quantSoldados);
	randNavioaAtacar = randNumber(navioaAtacar->getNumSoldados());
	cout << "This tem soldados: " << this->quantSoldados<<endl;
	cout << "Outro tem soldados: " << navioaAtacar->getNumSoldados()<<endl;
	if (randThis == randNavioaAtacar) //se houver empate
		randThis += 1; //o navio que ataca vai ganhar porque viu primeiro ;-)

	if (randThis > randNavioaAtacar) { // este ganhou
		cout << "Ganhou o this" << endl;
		soldadosPerdidos = (20 * this->quantSoldados) / 100;
		this->quantSoldados -= soldadosPerdidos;// este perdeu 20% da sua população
		navioaAtacar->setNumSoldados(navioaAtacar->getNumSoldados() - (soldadosPerdidos * 2));// o outro perde 2 vezes mais que o outro
		cout << "Agora o this tem: " << this->quantSoldados << "soldados" << endl;
		cout << "Agora o atacado tem: " << navioaAtacar->getNumSoldados() << "soldados" << endl;
		if (navioaAtacar->getNumSoldados() <= 0) {
			//set afundado
			navioaAtacar->setAfundado(true);
			//passar a metade da carga
			//passa a agua toda menos o execesso
		}
	}
	else { //o atacado ganhou 
		cout << "Ganhou o NAVIOaAaTACAR" << endl;
		soldadosPerdidos = (20 * navioaAtacar->getNumSoldados()) / 100;
		cout << "soldadosPerdidos  "<<soldadosPerdidos;
		navioaAtacar->setNumSoldados(navioaAtacar->getNumSoldados()-soldadosPerdidos);// o atacado perde 20% da sua população
		this->quantSoldados -= soldadosPerdidos * 2; //este perde 2 vezes mais que o outro
		cout << "Agora o atacado tem: " << navioaAtacar->getNumSoldados() << "soldados" << endl;
		cout << "Agora o this tem: " << this->quantSoldados << "soldados" << endl;
		if (this->quantSoldados <= 0) {
			//set afundar 
			this->setAfundado(true);
			//passar a metade da carga
			//passa a agua toda menos o execesso
		}
	}

}

void Navios::combate() {

	int xNavio = getX(), yNavio = getY();

	if (mundo->verificaCelulaNavio(xNavio + 1, yNavio) == CELULA_NAVIO) {
		acao(xNavio + 1, yNavio);
		cout << "Tenho um Navio para atacar à minha direita" << endl;
	}
	if (mundo->verificaCelulaNavio(xNavio - 1, yNavio) == CELULA_NAVIO ) {
		acao(xNavio - 1, yNavio);
		cout << "Tenho um Navio para atacar à minha esquerda" << endl;
	}
	if (mundo->verificaCelulaNavio(xNavio, yNavio-1) == CELULA_NAVIO ) {
		acao(xNavio, yNavio - 1);
		cout << "Tenho um Navio para atacar em cima" << endl;
	}
	if (mundo->verificaCelulaNavio(xNavio, yNavio+1) == CELULA_NAVIO ) {
		acao(xNavio, yNavio + 1);
		cout << "Tenho um Navio para atacar em baixo" << endl;
	}
	if (mundo->verificaCelulaNavio(xNavio + 1, yNavio-1) == CELULA_NAVIO ) {
		acao(xNavio + 1, yNavio - 1);
		cout << "Tenho um Navio para atacar à minha cima direita" << endl;
	}
	if (mundo->verificaCelulaNavio(xNavio-1, yNavio-1) == CELULA_NAVIO ) {
		acao(xNavio - 1, yNavio - 1);
		cout << "Tenho um Navio para atacar à minha cima esquerda" << endl;
	}
	if (mundo->verificaCelulaNavio(xNavio + 1, yNavio+1) == CELULA_NAVIO ) {
		acao(xNavio + 1, yNavio + 1);
		cout << "Tenho um Navio para atacar à minha baixo direita" << endl;
	}
	if (mundo->verificaCelulaNavio(xNavio - 1, yNavio + 1) == CELULA_NAVIO) {
		acao(xNavio - 1, yNavio + 1);
		cout << "Tenho um Navio para atacar à minha baixo esquerda" << endl;
	}
	if (mundo->verificaCelulaPorto(xNavio, yNavio) == CELULA_PORTO_INIMIGO) {
		//acao(xNavio, yNavio);
		cout << "Porrada com o Porto Inimigo" << endl;
	}
	mundo->retiraNavAfundados();
}
int Navios::getNumSoldados() {
	return this->quantSoldados;
}
void Navios::setNumSoldados(int num) {
	this->quantSoldados = num;
}
int Navios::FmoveEsquerda() {
	int VerificaPorto = 0;
	//e ver se a nova pos está dentro de agua!
	if (x > 0 && (mundo->verificaCelulaMar(this->x - 1, this->y) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(this->x - 1, this->y);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = this->x - 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x - 1, this->y) != CELULA_NAVIO) {

				this->x = this->x - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;

			}
		}
		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = this->x - 1;
			return MOVE_VALIDO;
		}
	}
	else {

		if (x == 0 && (mundo->verificaCelulaMar(mundo->getDimX() - 1, this->y) == CELULA_MAR))

			VerificaPorto = mundo->verificaCelulaPorto(mundo->getDimX() - 1, this->y);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = mundo->getDimX() - 1;

			return MOVE_VALIDO;
		}
		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(mundo->getDimX() - 1, this->y) != CELULA_NAVIO) {

				this->x = mundo->getDimX() - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;

			}
		}
		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = mundo->getDimX() - 1;
			return MOVE_VALIDO;
		}
	}
	return MOVE_INVALIDO;
}
int Navios::FmoveDireita() {
	int VerificaPorto = 0;
	//e ver se a nova pos está dentro de agua!
	if (x < mundo->getDimX() - 1 && (mundo->verificaCelulaMar(this->x + 1, this->y) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(this->x + 1, this->y);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = this->x + 1;

			return MOVE_VALIDO;
		}
		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x + 1, this->y) != CELULA_NAVIO) {

				this->x = this->x + 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;

			}
		}
		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = this->x + 1;
			return MOVE_VALIDO;
		}
	}
	else {
		if (x == mundo->getDimX() - 1 && (mundo->verificaCelulaMar(0, this->y) == CELULA_MAR)) {

			VerificaPorto = mundo->verificaCelulaPorto(0, this->y);

			if (VerificaPorto == CELULA_PORTO_AMIGO) {

				this->x = 0;

				return MOVE_VALIDO;
			}

			if (VerificaPorto == CELULA_SEM_PORTO) {

				if (mundo->verificaCelulaNavio(0, this->y) != CELULA_NAVIO) {

					this->x = 0;

					return MOVE_VALIDO;
				}
				else {

					return MOVE_INVALIDO;

				}
			}

			if (VerificaPorto == CELULA_PORTO_INIMIGO) {
				this->x = 0;
				return MOVE_VALIDO;
			}
		}
	}
	return MOVE_INVALIDO;
}
int Navios::FmoveCima() {
	int VerificaPorto = 0;
	//e ver se a nova pos está dentro de agua!
	if (y > 0 && (mundo->verificaCelulaMar(this->x, this->y - 1) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(this->x, this->y - 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->y = this->y - 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x, this->y - 1) != CELULA_NAVIO) {

				this->y = this->y - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;

			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->y = this->y - 1;
			return MOVE_VALIDO;
		}

	}
	else {

		if (y == 0 && (mundo->verificaCelulaMar(this->x, mundo->getDimY() - 1) == CELULA_MAR)) {

			VerificaPorto = mundo->verificaCelulaPorto(this->x, mundo->getDimY() - 1);

			if (VerificaPorto == CELULA_PORTO_AMIGO) {

				this->y = mundo->getDimY() - 1;

				return MOVE_VALIDO;
			}

			if (VerificaPorto == CELULA_SEM_PORTO) {

				if (mundo->verificaCelulaNavio(this->x, mundo->getDimY() - 1) != CELULA_NAVIO) {

					this->y = mundo->getDimY() - 1;

					return MOVE_VALIDO;

				}
				else {

					return MOVE_INVALIDO;
				}
			}
			if (VerificaPorto == CELULA_PORTO_INIMIGO) {
				this->y = mundo->getDimY() - 1;
				return MOVE_VALIDO;
			}
		}
	}

	return MOVE_INVALIDO;
}
int Navios::FmoveBaixo() {
	int VerificaPorto = 0;
	//e ver se a nova pos está dentro de agua!
	if (y < mundo->getDimY() - 1 && (mundo->verificaCelulaMar(this->x, this->y + 1) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(this->x, this->y + 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->y = this->y + 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x, this->y + 1) != CELULA_NAVIO) {

				this->y = this->y + 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}
		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->y = this->y + 1;
			return MOVE_VALIDO;
		}

	}
	else {

		if (y == mundo->getDimY() - 1 && (mundo->verificaCelulaMar(this->x, 0) == CELULA_MAR)) {

			VerificaPorto = mundo->verificaCelulaPorto(this->x, 0);

			if (VerificaPorto == CELULA_PORTO_AMIGO) {

				this->y = 0;

				return MOVE_VALIDO;
			}

			if (VerificaPorto == CELULA_SEM_PORTO) {

				if (mundo->verificaCelulaNavio(this->x, 0) != CELULA_NAVIO) {

					this->y = 0;

					return MOVE_VALIDO;
				}
				else {

					return MOVE_INVALIDO;
				}
			}
			if (VerificaPorto == CELULA_PORTO_INIMIGO) {
				this->y = 0;
				return MOVE_VALIDO;
			}
		}
	}
	return MOVE_INVALIDO;
}
int Navios::FmoveCimaEsquerda() {
	int VerificaPorto = 0;
	//anda normal
	if ((y > 0 && y <= mundo->getDimY() - 1) && (x > 0 && x <= mundo->getDimX() - 1) && (mundo->verificaCelulaMar(this->x - 1, this->y - 1) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(this->x - 1, this->y - 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->y = this->y - 1;

			this->x = this->x - 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x - 1, this->y - 1) != CELULA_NAVIO) {

				this->y = this->y - 1;

				this->x = this->x - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->y = this->y - 1;
			this->x = this->x - 1;
			return MOVE_VALIDO;
		}

	}
	////encostado a cima
	if ((y == 0 && (x > 0 && x <= mundo->getDimX() - 1)) && (mundo->verificaCelulaMar(this->x - 1, mundo->getDimY() - 1) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(this->x - 1, mundo->getDimY() - 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = this->x - 1;

			this->y = mundo->getDimY() - 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x - 1, mundo->getDimY() - 1) != CELULA_NAVIO) {

				this->x = this->x - 1;

				this->y = mundo->getDimY() - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = this->x - 1;
			this->y = mundo->getDimY() - 1;
			return MOVE_VALIDO;
		}

	}
	////encostado à esquerda
	if ((x == 0 && (y > 0 && y <= mundo->getDimY() - 1)) && (mundo->verificaCelulaMar(mundo->getDimX() - 1, this->y - 1) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(mundo->getDimX() - 1, this->y - 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = mundo->getDimX() - 1;

			this->y = this->y - 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(mundo->getDimX() - 1, this->y - 1) != CELULA_NAVIO) {

				this->x = mundo->getDimX() - 1;

				this->y = this->y - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = mundo->getDimX() - 1;
			this->y = this->y - 1;
			return MOVE_VALIDO;
		}

	}
	//canto superior esquerdo
	if ((y == 0 && x == 0) && (mundo->verificaCelulaMar(mundo->getDimX() - 1, mundo->getDimY() - 1) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(mundo->getDimX() - 1, mundo->getDimY() - 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = mundo->getDimX() - 1;

			this->y = mundo->getDimY() - 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(mundo->getDimX() - 1, mundo->getDimY() - 1) != CELULA_NAVIO) {

				this->x = mundo->getDimX() - 1;

				this->y = mundo->getDimY() - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = mundo->getDimX() - 1;
			this->y = mundo->getDimY() - 1;
			return MOVE_VALIDO;
		}

	}
	return MOVE_INVALIDO;
}
int Navios::FmoveCimaDireita() {
	int VerificaPorto = 0;
	//anda normal
	if (y > 0 && y <= mundo->getDimY() - 1 && x > 0 && x < mundo->getDimX() - 1 && (mundo->verificaCelulaMar(this->x + 1, this->y - 1) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(this->x + 1, this->y - 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->y = this->y - 1;

			this->x = this->x + 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x + 1, this->y - 1) != CELULA_NAVIO) {

				this->y = this->y - 1;

				this->x = this->x + 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->y = this->y - 1;
			this->x = this->x + 1;
			return MOVE_VALIDO;
		}

	}
	//encostado a cima
	if ((y == 0 && (x >= 0 && x < mundo->getDimX() - 1)) && (mundo->verificaCelulaMar(this->x + 1, mundo->getDimY() - 1) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(this->x + 1, mundo->getDimY() - 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = this->x + 1;

			this->y = mundo->getDimY() - 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x + 1, mundo->getDimY() - 1) != CELULA_NAVIO) {

				this->x = this->x + 1;

				this->y = mundo->getDimY() - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = this->x + 1;
			this->y = mundo->getDimY() - 1;
			return MOVE_VALIDO;
		}

	}
	//encostado à direita
	if ((x == mundo->getDimX() - 1 && y > 0 && y <= mundo->getDimY() - 1) && (mundo->verificaCelulaMar(0, this->y - 1) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(0, this->y - 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = 0;

			this->y = this->y - 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(0, this->y - 1) != CELULA_NAVIO) {

				this->x = 0;

				this->y = this->y - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = 0;
			this->y = this->y - 1;
			return MOVE_VALIDO;
		}

	}
	//canto superior direito
	if (y == 0 && x == mundo->getDimX() - 1 && (mundo->verificaCelulaMar(0, mundo->getDimY() - 1) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(0, mundo->getDimY() - 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = 0;

			this->y = mundo->getDimY() - 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(0, mundo->getDimY() - 1) != CELULA_NAVIO) {

				this->x = 0;

				this->y = mundo->getDimY() - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = 0;
			this->y = mundo->getDimY() - 1;
			return MOVE_VALIDO;
		}
	}
	return MOVE_INVALIDO;
}
int Navios::FmoveBaixoEsquerda() {
	int VerificaPorto = 0;
	//anda normal
	if ((y >= 0 && y < mundo->getDimY() - 1) && (x > 0 && x <= mundo->getDimX() - 1) && (mundo->verificaCelulaMar(this->x - 1, this->y + 1) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(this->x - 1, this->y + 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->y = this->y + 1;

			this->x = this->x - 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x - 1, this->y + 1) != CELULA_NAVIO) {

				this->y = this->y + 1;

				this->x = this->x - 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->y = this->y + 1;
			this->x = this->x - 1;
			return MOVE_VALIDO;
		}
	}
	//////encostado a baixo
	if ((y == mundo->getDimY() - 1) && (x > 0 && x <= mundo->getDimX() - 1) && (mundo->verificaCelulaMar(this->x - 1, 0) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(this->x - 1, 0);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = this->x - 1;

			this->y = 0;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x - 1, 0) != CELULA_NAVIO) {

				this->x = this->x - 1;

				this->y = 0;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = this->x - 1;
			this->y = 0;
			return MOVE_VALIDO;
		}

	}
	//////encostado à esquerda
	if ((x == 0) && (y >= 0 && y < mundo->getDimY() - 1) && (mundo->verificaCelulaMar(mundo->getDimX() - 1, this->y + 1) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(mundo->getDimX() - 1, this->y + 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = mundo->getDimX() - 1;
			this->y = this->y + 1;
			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(mundo->getDimX() - 1, this->y + 1) != CELULA_NAVIO) {

				this->x = mundo->getDimX() - 1;

				this->y = this->y + 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = mundo->getDimX() - 1;
			this->y = this->y + 1;
			return MOVE_VALIDO;
		}
	}
	//canto inferior esquerdo
	if ((y == mundo->getDimY() - 1 && x == 0) && (mundo->verificaCelulaMar(mundo->getDimX() - 1, 0) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(mundo->getDimX() - 1, 0);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = mundo->getDimX() - 1;

			this->y = 0;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(mundo->getDimX() - 1, 0) != CELULA_NAVIO) {

				this->x = mundo->getDimX() - 1;

				this->y = 0;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = mundo->getDimX() - 1;
			this->y = 0;
			return MOVE_VALIDO;
		}
	}
	return MOVE_INVALIDO;
}
int Navios::FmoveBaixoDireita() {
	int VerificaPorto = 0;
	//anda normal
	if ((y >= 0 && y < mundo->getDimY() - 1) && (x >= 0 && x < mundo->getDimX() - 1) && (mundo->verificaCelulaMar(this->x + 1, this->y + 1) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(this->x + 1, this->y + 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->y = this->y + 1;

			this->x = this->x + 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x + 1, this->y + 1) != CELULA_NAVIO) {

				this->y = this->y + 1;

				this->x = this->x + 1;

				return MOVE_VALIDO;
			}
			else {
				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->y = this->y + 1;
			this->x = this->x + 1;
			return MOVE_VALIDO;
		}
	}
	////////encostado a baixo
	if ((y == mundo->getDimY() - 1) && (x >= 0 && x < mundo->getDimX() - 1) && (mundo->verificaCelulaMar(this->x + 1, 0) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(this->x + 1, 0);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = this->x + 1;

			this->y = 0;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x + 1, 0) != CELULA_NAVIO) {

				this->x = this->x + 1;

				this->y = 0;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = this->x + 1;
			this->y = 0;
			return MOVE_VALIDO;
		}

	}
	////////encostado à direita
	if ((x == mundo->getDimX() - 1) && (y >= 0 && y < mundo->getDimY() - 1) && (mundo->verificaCelulaMar(0, this->y + 1) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(0, this->y + 1);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = 0;

			this->y = this->y + 1;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(0, this->y + 1) != CELULA_NAVIO) {

				this->x = 0;

				this->y = this->y + 1;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = 0;
			this->y = this->y + 1;
			return MOVE_VALIDO;
		}
	}
	////canto inferior esquerdo
	if ((y == mundo->getDimY() - 1 && x == mundo->getDimX() - 1) && (mundo->verificaCelulaMar(0, 0) == CELULA_MAR)) {

		VerificaPorto = mundo->verificaCelulaPorto(0, 0);

		if (VerificaPorto == CELULA_PORTO_AMIGO) {

			this->x = 0;

			this->y = 0;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(0, this->y + 1) != CELULA_NAVIO) {

				this->x = 0;

				this->y = 0;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO){
			this->x = 0;
			this->y = 0;
			return MOVE_VALIDO;
		}
	}
	return MOVE_INVALIDO;
}
int Navios::moveNavio(int direcao) {

	switch (direcao) {

	case moveEsquerda:
		if (FmoveEsquerda() == MOVE_VALIDO) {
			return MOVE_VALIDO;
			}
		else
			break;
	case moveDireita:
		if (FmoveDireita() == MOVE_VALIDO) {
			return MOVE_VALIDO;
		}
		else
			break;
	case moveCima:
		if (FmoveCima() == MOVE_VALIDO) {
			return MOVE_VALIDO;
		}
		else
			break;
	case moveBaixo:
		if (FmoveBaixo() == MOVE_VALIDO) {
			return MOVE_VALIDO;
		}
		else
			break;
	case moveCimaEsquerda:
		if (FmoveCimaEsquerda() == MOVE_VALIDO) {
			return MOVE_VALIDO;
		}
		else
			break;
	case moveCimaDireita:
		if (FmoveCimaDireita() == MOVE_VALIDO) {
			return MOVE_VALIDO;
		}
		else
			break;
	case moveBaixoEsquerda:
		if (FmoveBaixoEsquerda() == MOVE_VALIDO) {
			return MOVE_VALIDO;
		}
		else
			break;
	case moveBaixoDireita:
		if (FmoveBaixoDireita() == MOVE_VALIDO) {
			return MOVE_VALIDO;
		}
		else
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
