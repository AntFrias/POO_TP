#include "Veleiro.h"
#include "Mundo.h"



void Veleiro::AbasteceAguaNavio()
{
	this->quantAgua = VELEIRO_MAX_AGUA;
	
}
string Veleiro::moveNavioAuto() {

	ostringstream os;

	unsigned int direcao;
	direcao = rand() % 9 + 1;
	this->moveNavio(direcao);

	switch (this->estado)
	{
	case autoMove:
		this->soldadosBebemAgua();
		os<<this->combate(CELULA_NAVIO_PIRATA);
		break;

	case pirata:
		os<<this->combate(CELULA_NAVIO_NORMAL);
		break;

	}
	return os.str();
}

void Veleiro::soldadosBebemAgua() {
	if (mundo->verificaCelulaMar(this->x, this->y) || (mundo->verificaCelulaPorto(this->x, this->y) != CELULA_PORTO_AMIGO)) {
		if (this->quantAgua > 0)
			this->quantAgua -= this->getNumSoldados();
	}
	if (this->quantAgua <= 0) {
		if (this->quantSoldados > 0) {
			this->quantSoldados -= 1;
		}
		if (this->quantSoldados == 0) {
			this->estado = aDeriva;
		}
	}
}

int Veleiro::getMaxAgua() {
	return VELEIRO_MAX_AGUA;
}
int Veleiro::getAgua() {
	return this->quantAgua;
}
void Veleiro::adicionaAgua(int agua) {
	this->quantAgua += agua;
}
int Veleiro::sou() {
	return VELEIRO;
}
void Veleiro::conquistaPorto(int xPorto, int yPorto) {

	char lastPortoAmigo = 'Z';

	// ultimo porto amigo
	lastPortoAmigo = mundo->LastPortoAmigo();
	//
	mundo->mudaPorto(xPorto, yPorto, lastPortoAmigo + 1);


}
string Veleiro::acaoPorto() {

	ostringstream os;
	int sorteio = 0, soldadosPerdidos = 0;

	sorteio = randNumber(100);

	if (sorteio <= this->getNumSoldados()) {// o navio ganhou e conquista o porto
		soldadosPerdidos = (10 * this->getNumSoldados()) / 100;
		this->setNumSoldados(this->getNumSoldados() - soldadosPerdidos);

		//conquista Porto
		conquistaPorto(this->x, this->y);
		os << " O Porto foi conquistado ! " << endl;
		os << " O Navio " << this->getId() << " ficou com " << this->getNumSoldados() << " soldados" << endl;
		if (this->quantSoldados <= 0) {
			this->estado = afundado;
			os << " O Navio " << this->getId() << " afundou " << endl;
		}
		if (this->quantSoldados <= 0)
			this->estado = afundado;
	}
	else {
		soldadosPerdidos = (10 * this->getNumSoldados()) / 100;
		this->setNumSoldados(this->getNumSoldados() - soldadosPerdidos);
		os << " O Porto nao foi conquistado ! " << endl;
		os << " O Navio " << this->getId() << " ficou com " << this->getNumSoldados() << " soldados" << endl;
		if (this->quantSoldados <= 0) {
			this->estado = afundado;
			os << " O Navio " << this->getId() << " afundou " << endl;
		}
	}
	return os.str();
}
string Veleiro::acao(int xaAtacar, int yaAtacar) {

	ostringstream os;

	Navios *navioaAtacar = nullptr;
	navioaAtacar = mundo->getNavioXY(xaAtacar, yaAtacar);
	int randThis = 0, randNavioaAtacar = 0, soldadosPerdidos = 0;
	os << "----------------------------Combate----------------------------" << endl;
	os << "O " << this->getId() << "moveu-se e encontrou o: " << navioaAtacar->getId() << endl;

	randThis = randNumber(this->quantSoldados);
	randNavioaAtacar = randNumber(navioaAtacar->getNumSoldados());

	os << "O " << this->getId() << "ficou com o nr sorteado: " << randThis << "e tem neste momento " << this->quantSoldados << "soldados" << endl;
	os << "O " << navioaAtacar->getId() << "ficou com o nr sorteado: " << randNavioaAtacar << "e tem neste momento" << navioaAtacar->getNumSoldados() << "soldados" << endl;


	if (randThis == randNavioaAtacar) //se houver empate
		randThis += 1; //o navio que ataca vai ganhar porque viu primeiro ;-)

	if (randThis > randNavioaAtacar) { // este ganhou
		soldadosPerdidos = (20 * this->quantSoldados) / 100;
		if (soldadosPerdidos == 0)
			soldadosPerdidos = 1;
		os << "O Navio " << this->getId() << " ganhou esta investida, ira perder " << soldadosPerdidos << " soldados." << endl;
		os << "O Navio " << navioaAtacar->getId() << " perdeu esta investida, ira perder " << soldadosPerdidos * 2 << " soldados." << endl;
		this->quantSoldados -= soldadosPerdidos;// este perdeu 20% da sua população
		navioaAtacar->setNumSoldados(navioaAtacar->getNumSoldados() - (soldadosPerdidos * 2));// o outro perde 2 vezes mais que o outro

		if (navioaAtacar->getNumSoldados() <= 0) {
			//set afundado
			navioaAtacar->setEstado(afundado);
			//passar a metade da carga
			//passa a agua toda menos o execesso
			if (this->getAgua() + navioaAtacar->getAgua() > this->getMaxAgua()) {
				this->adicionaAgua(this->getMaxAgua() - this->getAgua());
			}
			else
				this->adicionaAgua(navioaAtacar->getAgua());
		}
		os << "O Navio " << this->getId() << " ficou com  " << this->quantSoldados << "soldados." << endl;
		os << "O Navio " << navioaAtacar->getId() << " ficou com " << navioaAtacar->getNumSoldados() << "soldados." << endl;
	}
	else { //o atacado ganhou 

		soldadosPerdidos = (20 * navioaAtacar->getNumSoldados()) / 100;
		if (soldadosPerdidos == 0)
			soldadosPerdidos = 1;
		os << "O Navio " << this->getId() << " perdeu esta investida, ira perder " << soldadosPerdidos * 2 << "soldados." << endl;
		os << "O Navio " << navioaAtacar->getId() << " ganhour esta investida, ira perder " << soldadosPerdidos << "soldados." << endl;
		navioaAtacar->setNumSoldados(navioaAtacar->getNumSoldados() - soldadosPerdidos);// o atacado perde 20% da sua população
		this->quantSoldados -= soldadosPerdidos * 2; //este perde 2 vezes mais que o outro

		if (this->quantSoldados <= 0) {
			//set afundar 
			this->estado = afundado;
			//passar a metade da carga
			//passa a agua toda menos o execesso
			if (navioaAtacar->getAgua() + this->getAgua() > navioaAtacar->getMaxAgua()) {
				navioaAtacar->adicionaAgua(navioaAtacar->getMaxAgua() - navioaAtacar->getAgua());
			}
			else
				navioaAtacar->adicionaAgua(this->getAgua());

		}
		os << "O Navio " << this->getId() << " ficou com  " << this->quantSoldados << " soldados." << endl;
		os << "O Navio " << navioaAtacar->getId() << " ficou com " << navioaAtacar->getNumSoldados() << " soldados." << endl;
	}
	os << "---------------------------------------------------------------" << endl;
	return os.str();
}
string Veleiro::combate(int quemVouAtacar) {

	int xNavio = getX(), yNavio = getY();
	ostringstream os;

	if (mundo->verificaCelulaNavioPirata(xNavio + 1, yNavio) == quemVouAtacar && (!mundo->verificaCelulaNavioDeriva(xNavio + 1, yNavio))) {
		os << acao(xNavio + 1, yNavio);
	}
	if (mundo->verificaCelulaNavioPirata(xNavio - 1, yNavio) == quemVouAtacar && (!mundo->verificaCelulaNavioDeriva(xNavio - 1, yNavio))) {
		os << acao(xNavio - 1, yNavio);
	}
	if (mundo->verificaCelulaNavioPirata(xNavio, yNavio - 1) == quemVouAtacar && (!mundo->verificaCelulaNavioDeriva(xNavio, yNavio - 1))) {
		os << acao(xNavio, yNavio - 1);
	}
	if (mundo->verificaCelulaNavioPirata(xNavio, yNavio + 1) == quemVouAtacar && (!mundo->verificaCelulaNavioDeriva(xNavio, yNavio + 1))) {
		os << acao(xNavio, yNavio + 1);
	}
	if (mundo->verificaCelulaNavioPirata(xNavio + 1, yNavio - 1) == quemVouAtacar && (!mundo->verificaCelulaNavioDeriva(xNavio + 1, yNavio - 1))) {
		os << acao(xNavio + 1, yNavio - 1);
	}
	if (mundo->verificaCelulaNavioPirata(xNavio - 1, yNavio - 1) == quemVouAtacar && (!mundo->verificaCelulaNavioDeriva(xNavio - 1, yNavio - 1))) {
		os << acao(xNavio - 1, yNavio - 1);
	}
	if (mundo->verificaCelulaNavioPirata(xNavio + 1, yNavio + 1) == quemVouAtacar && (!mundo->verificaCelulaNavioDeriva(xNavio + 1, yNavio + 1))) {
		os << acao(xNavio + 1, yNavio + 1);
	}
	if (mundo->verificaCelulaNavioPirata(xNavio - 1, yNavio + 1) == quemVouAtacar && (!mundo->verificaCelulaNavioDeriva(xNavio - 1, yNavio + 1))) {
		os << acao(xNavio - 1, yNavio + 1);
	}
	if (quemVouAtacar == CELULA_NAVIO_PIRATA) {
		if (mundo->verificaCelulaPorto(xNavio, yNavio) == CELULA_PORTO_INIMIGO) {
			acaoPorto();
			cout << "Porrada com o Porto Inimigo" << endl;
		}
	}

	if (quemVouAtacar == CELULA_NAVIO_NORMAL) {
		if (mundo->verificaCelulaPorto(xNavio, yNavio) == CELULA_PORTO_AMIGO) {
			acaoPorto();
			cout << "Porrada com o Porto Inimigo" << endl;
		}
	}

	return os.str();
}
int Veleiro::FmoveEsquerda() {
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
int Veleiro::FmoveDireita() {
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
int Veleiro::FmoveCima() {
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
int Veleiro::FmoveBaixo() {
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
int Veleiro::FmoveCimaEsquerda() {
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
int Veleiro::FmoveCimaDireita() {
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
int Veleiro::FmoveBaixoEsquerda() {
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
int Veleiro::FmoveBaixoDireita() {
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

		if (VerificaPorto == CELULA_PORTO_INIMIGO) {
			this->x = 0;
			this->y = 0;
			return MOVE_VALIDO;
		}
	}
	return MOVE_INVALIDO;
}
void Veleiro::serConquistadoaDeriva() {

	int x = this->x, y = this->y;
	switch (mundo->verificaCelulaNavioPirata(x + 1, y)) {
	case CELULA_NAVIO_NORMAL:
		this->estado = normal;
		daMetade(x + 1, y);
		break;
	case CELULA_NAVIO_PIRATA:
		this->estado = pirata;
		daMetade(x + 1, y);
		break;
	default:
		break;
	}
	switch (mundo->verificaCelulaNavioPirata(x - 1, y)) {
	case CELULA_NAVIO_NORMAL:
		this->estado = normal;
		daMetade(x - 1, y);
		break;
	case CELULA_NAVIO_PIRATA:
		this->estado = pirata;
		daMetade(x - 1, y);
		break;
	default:
		break;
	}
	switch (mundo->verificaCelulaNavioPirata(x, y - 1)) {
	case CELULA_NAVIO_NORMAL:
		this->estado = normal;
		daMetade(x, y - 1);
		break;
	case CELULA_NAVIO_PIRATA:
		this->estado = pirata;
		daMetade(x, y - 1);
		break;
	default:
		break;
	}
	switch (mundo->verificaCelulaNavioPirata(x, y + 1)) {
	case CELULA_NAVIO_NORMAL:
		this->estado = normal;
		daMetade(x, y + 1);
		break;
	case CELULA_NAVIO_PIRATA:
		this->estado = pirata;
		daMetade(x, y + 1);
		break;
	default:
		break;
	}
	switch (mundo->verificaCelulaNavioPirata(x + 1, y - 1)) {
	case CELULA_NAVIO_NORMAL:
		this->estado = normal;
		daMetade(x + 1, y - 1);
		break;
	case CELULA_NAVIO_PIRATA:
		this->estado = pirata;
		daMetade(x + 1, y - 1);
		break;
	default:
		break;
	}
	switch (mundo->verificaCelulaNavioPirata(x - 1, y - 1)) {
	case CELULA_NAVIO_NORMAL:
		this->estado = normal;
		daMetade(x - 1, y - 1);
		break;
	case CELULA_NAVIO_PIRATA:
		this->estado = pirata;
		daMetade(x - 1, y - 1);
		break;
	default:
		break;
	}
	switch (mundo->verificaCelulaNavioPirata(x + 1, y + 1)) {
	case CELULA_NAVIO_NORMAL:
		this->estado = normal;
		daMetade(x + 1, y + 1);
		break;
	case CELULA_NAVIO_PIRATA:
		this->estado = pirata;
		daMetade(x + 1, y + 1);
		break;
	default:
		break;
	}
	switch (mundo->verificaCelulaNavioPirata(x - 1, y + 1)) {
	case CELULA_NAVIO_NORMAL:
		this->estado = normal;
		daMetade(x - 1, y + 1);
		break;
	case CELULA_NAVIO_PIRATA:
		this->estado = pirata;
		daMetade(x - 1, y + 1);
		break;
	default:
		break;
	}

}
void Veleiro::retiraAgua(int agua) {

	this->quantAgua -= agua;

}
void Veleiro::retiraSoldados(int soldados) {

	this->quantSoldados -= soldados;

}
int Veleiro::getMaxSoldados() {
	return VELEIRO_MAX_SOLDADOS;
}
void Veleiro::daMetade(int x, int y) {

	Navios *auxNavio = nullptr;
	auxNavio = mundo->getNavioXY(x, y);
	if (auxNavio->getNumSoldados() > 0) {
		//fico com metade para mim  soldados e agua
		this->quantAgua = auxNavio->getAgua() / 2;
		this->quantSoldados = auxNavio->getNumSoldados() / 2;
		//tira metade ao que da soldados e agua
		auxNavio->retiraAgua(auxNavio->getAgua() / 2);
		auxNavio->retiraSoldados(auxNavio->getNumSoldados() / 2);
	}
	else
		this->estado = aDeriva;
}
int Veleiro::moveNavio(int direcao) {

	switch (direcao) {
		
	case moveEsquerda:
		if (FmoveEsquerda() == MOVE_VALIDO) {
			this->soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveDireita:
		if (FmoveDireita() == MOVE_VALIDO) {
			this->soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveCima:
		if (FmoveCima() == MOVE_VALIDO) {
			this->soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveBaixo:
		if (FmoveBaixo() == MOVE_VALIDO) {
			this->soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveCimaEsquerda:
		if (FmoveCimaEsquerda() == MOVE_VALIDO) {
			this->soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveCimaDireita:
		if (FmoveCimaDireita() == MOVE_VALIDO) {
			this->soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveBaixoEsquerda:
		if (FmoveBaixoEsquerda() == MOVE_VALIDO) {
			this->soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveBaixoDireita:
		if (FmoveBaixoDireita() == MOVE_VALIDO) {
			this->soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	}
	return MOVE_INVALIDO;
}
void Veleiro::setCargaNavio(int quantCarga)
{
	if (this->QuantMercadoria + quantCarga <= VELEIRO_QUANT_MAX_CARGA)
		this->QuantMercadoria = QuantMercadoria + quantCarga;
	else
		this->QuantMercadoria = VELEIRO_QUANT_MAX_CARGA;
}
void Veleiro::RetiraCargaNavio(int quantCarga)
{
	if (this->QuantPeixe - (quantCarga / 2) >= 0)
		this->QuantPeixe = this->QuantPeixe - (quantCarga / 2);

	if (this->QuantMercadoria - quantCarga >= 0)
		this->QuantMercadoria = QuantMercadoria - quantCarga;
	else
		this->QuantMercadoria = 0;
}
string Veleiro::TrataNavioTempestade()
{
	ostringstream os;

	os << "O navio é do tipo Veleiro" << endl;

	int QuantCarga = ( this->QuantMercadoria * 100 ) / VELEIRO_QUANT_MAX_CARGA;

	int probAfundar = rand() % 100 + 1;

	if (probAfundar <= PROB_VELEIRO_AFUNDAR_TEMPESTADE_1 && QuantCarga >= PROB_VELEIRO_PERDER_CARGA)
		this->estado = afundado;

	else if (probAfundar <= PROB_VELEIRO_AFUNDAR_TEMPESTADE_2)  // aqui a probabilidade é diferente pelo facto do 
		this->estado = afundado;    							//navio pedir apenas 20% de prob caso tenha menos que 50%
																// de capacidade de carga
	else
	{
		RetiraCargaNavio( QuantMercadoria / 2 );
	}
	AbasteceAguaNavio();

	return os.str();
}
bool Veleiro::VerificaCargaNavio(int novaCarga)
{
	if (this->QuantMercadoria + novaCarga <= VELEIRO_QUANT_MAX_CARGA)
		return true;
	else
		return false;
}
Veleiro::~Veleiro()
{
}
