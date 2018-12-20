#include "Fragata.h"
#include "Mundo.h"

void Fragata::AbasteceAguaNavio()
{
	this->quantAgua = FRAGATA_MAX_AGUA;
}
void Fragata::soldadosBebemAgua() {

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
void Fragata::moveNavioAuto() {

	unsigned int direcao;
	direcao = rand() % 9 + 1;
	this->moveNavio(direcao);

	switch (this->estado) 
	{
		case autoMove:
			this->soldadosBebemAgua();
			this->combate();
			break;

		case pirata: 
			this->combate();
			break;

	}
}
int Fragata::sou() {

	return FRAGATA;

}
int Fragata::getMaxAgua() {
	return FRAGATA_MAX_AGUA;
}
int Fragata::getAgua() {
	return this->quantAgua;
}
void Fragata::adicionaAgua(int agua) {
	this->quantAgua += agua;
}
string Fragata::acao(int xaAtacar, int yaAtacar) {

	ostringstream os;


	Navios *navioaAtacar = nullptr;
	navioaAtacar = mundo->getNavioXY(xaAtacar, yaAtacar);
	int randThis = 0, randNavioaAtacar = 0, soldadosPerdidos = 0;
	os << "---------------Combate------------------" << endl;
	os << "O " << this->getId() << " moveu-se e encontrou o: " << navioaAtacar->getId() << endl;

	randThis = randNumber(this->quantSoldados);
	randNavioaAtacar = randNumber(navioaAtacar->getNumSoldados());

	os << "O " << this->getId() << " ficou com o nr sorteado: " << randThis << " e tem neste momento " << this->quantSoldados << " soldados " << endl;
	os << "O " << navioaAtacar->getId() << " ficou com o nr sorteado: " << randNavioaAtacar << " e tem neste momento " << navioaAtacar->getNumSoldados() << " soldados " << endl;


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
			//-> Fragata não tem carga n passa nada
			//passa a agua toda menos o execesso
			if (this->getAgua() + navioaAtacar->getAgua() > this->getMaxAgua()) {
				this->adicionaAgua(this->getMaxAgua() - this->getAgua());
			}
			else
				this->adicionaAgua(navioaAtacar->getAgua());
		
		}
		os << "O Navio " << this->getId() << " ficou com " << this->quantSoldados << " soldados." << endl;
		os << "O Navio " << navioaAtacar->getId() << " ficou com " << navioaAtacar->getNumSoldados() << " soldados." << endl;
	}
	else { //o atacado ganhou 

		soldadosPerdidos = (20 * navioaAtacar->getNumSoldados()) / 100;
		if (soldadosPerdidos == 0)
			soldadosPerdidos = 1;
		os << "O Navio " << this->getId() << " perdeu esta investida, ira perder " << soldadosPerdidos * 2 << " soldados." << endl;
		os << "O Navio " << navioaAtacar->getId() << " ganhour esta investida, ira perder " << soldadosPerdidos << " soldados." << endl;
		navioaAtacar->setNumSoldados(navioaAtacar->getNumSoldados() - soldadosPerdidos);// o atacado perde 20% da sua população
		this->quantSoldados -= soldadosPerdidos * 2; //este perde 2 vezes mais que o outro

		if (this->quantSoldados <= 0) {
			//set afundar 
			this->estado = afundado;
			//passar a metade da carga
			//-> Fragata não tem carga n passa nada
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
	os << "-------------Fim_Combate----------------" << endl<< endl;
	return os.str();
}
void Fragata::conquistaPorto(int xPorto,int yPorto) {
	
	char lastPortoAmigo = 'Z';

	// ultimo porto amigo
	lastPortoAmigo=mundo->LastPortoAmigo();
	//
	mundo->mudaPorto(xPorto, yPorto,lastPortoAmigo+1);


}
string Fragata::acaoPorto() {

	ostringstream os;
	int sorteio = 0,soldadosPerdidos =0;

	sorteio = randNumber(100);

	if (sorteio <= this->getNumSoldados()) {// o navio ganhou e conquista o porto
		soldadosPerdidos = (10 * this->getNumSoldados()) / 100;
		this->setNumSoldados( this->getNumSoldados() - soldadosPerdidos);
		
		//conquista Porto
		conquistaPorto(this->x,this->y);
		os << " O Porto foi conquistado ! " << endl;
		os << " O Navio " << this->getId() << " ficou com " << this->getNumSoldados() << " soldados" << endl;
		if (this->quantSoldados <= 0) {
			this->estado = afundado;
			os << " O Navio " << this->getId() << " afundou " << endl;
		}
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
string Fragata::combate() {

	int xNavio = getX(), yNavio = getY();
	ostringstream os;
	if (this->estado == normal) {
		if (mundo->verificaCelulaNavioPirata(xNavio + 1, yNavio) == CELULA_NAVIO_PIRATA) {
			os << acao(xNavio + 1, yNavio);
		}
		if (mundo->verificaCelulaNavioPirata(xNavio - 1, yNavio) == CELULA_NAVIO_PIRATA) {
			os << acao(xNavio - 1, yNavio);
		}
		if (mundo->verificaCelulaNavioPirata(xNavio, yNavio - 1) == CELULA_NAVIO_PIRATA) {
			os << acao(xNavio, yNavio - 1);
		}
		if (mundo->verificaCelulaNavioPirata(xNavio, yNavio + 1) == CELULA_NAVIO_PIRATA) {
			os << acao(xNavio, yNavio + 1);
		}
		if (mundo->verificaCelulaNavioPirata(xNavio + 1, yNavio - 1) == CELULA_NAVIO_PIRATA) {
			os << acao(xNavio + 1, yNavio - 1);
		}
		if (mundo->verificaCelulaNavioPirata(xNavio - 1, yNavio - 1) == CELULA_NAVIO_PIRATA) {
			os << acao(xNavio - 1, yNavio - 1);
		}
		if (mundo->verificaCelulaNavioPirata(xNavio + 1, yNavio + 1) == CELULA_NAVIO_PIRATA) {
			os << acao(xNavio + 1, yNavio + 1);
		}
		if (mundo->verificaCelulaNavioPirata(xNavio - 1, yNavio + 1) == CELULA_NAVIO_PIRATA) {
			os << acao(xNavio - 1, yNavio + 1);
		}
		if (mundo->verificaCelulaPorto(xNavio, yNavio) == CELULA_PORTO_INIMIGO) {
			acaoPorto();
			cout << "Porrada com o Porto Inimigo" << endl;
		}
	}
	if(this->estado==pirata) { // se é pirata
		if (mundo->verificaCelulaNavioPirata(xNavio + 1, yNavio) == CELULA_NAVIO_NORMAL) {
			os << acao(xNavio + 1, yNavio);
		}
		if (mundo->verificaCelulaNavioPirata(xNavio - 1, yNavio) == CELULA_NAVIO_NORMAL) {
			os << acao(xNavio - 1, yNavio);
		}
		if (mundo->verificaCelulaNavioPirata(xNavio, yNavio - 1) == CELULA_NAVIO_NORMAL) {
			os << acao(xNavio, yNavio - 1);
		}
		if (mundo->verificaCelulaNavioPirata(xNavio, yNavio + 1) == CELULA_NAVIO_NORMAL) {
			os << acao(xNavio, yNavio + 1);
		}
		if (mundo->verificaCelulaNavioPirata(xNavio + 1, yNavio - 1) == CELULA_NAVIO_NORMAL) {
			os << acao(xNavio + 1, yNavio - 1);
		}
		if (mundo->verificaCelulaNavioPirata(xNavio - 1, yNavio - 1) == CELULA_NAVIO_NORMAL) {
			os << acao(xNavio - 1, yNavio - 1);
		}
		if (mundo->verificaCelulaNavioPirata(xNavio + 1, yNavio + 1) == CELULA_NAVIO_NORMAL) {
			os << acao(xNavio + 1, yNavio + 1);
		}
		if (mundo->verificaCelulaNavioPirata(xNavio - 1, yNavio + 1) == CELULA_NAVIO_NORMAL) {
			os << acao(xNavio - 1, yNavio + 1);
		}
		if (mundo->verificaCelulaPorto(xNavio, yNavio) == CELULA_PORTO_AMIGO) {
			acaoPorto();
			cout << "Porrada com o Porto Inimigo" << endl;
		}
	}
	return os.str();
}
void Fragata::setCargaNavio(int quantCarga)
{
}
void Fragata::RetiraCargaNavio(int quantCarga)
{
}
string Fragata::TrataNavioTempestade()
{
	ostringstream os;

	os << "O navio é do tipo Fragata" << endl;

	if (rand() % 100 + 1 <= PROB_FRAGATA_AFUNDAR_TEMPESTADE)
		this->estado = afundado;

	else {

		this->quantSoldados = this->quantSoldados - ((quantSoldados * 15) / 100);
		
		AbasteceAguaNavio();
	}
	return os.str();
}
int Fragata::FmoveEsquerda() {
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
int Fragata::FmoveDireita() {
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
int Fragata::FmoveCima() {
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
int Fragata::FmoveBaixo() {
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
int Fragata::FmoveCimaEsquerda() {
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
int Fragata::FmoveCimaDireita() {
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
int Fragata::FmoveBaixoEsquerda() {
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
int Fragata::FmoveBaixoDireita() {
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
int Fragata::moveNavio(int direcao) {
		
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
Fragata::~Fragata()
{
}
