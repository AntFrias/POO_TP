#include "Tartaruga.h"
#include "Mundo.h"

Navios * Tartaruga::Duplica() const
{
	return new Tartaruga(*this);
}

void Tartaruga::AbasteceAguaNavio()
{
	this->quantAgua = TARTARUGA_MAX__AGUA;
}
void Tartaruga::soldadosBebemAgua() {

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
void Tartaruga::retiraAgua(int agua) {

	this->quantAgua -= agua;

}
void Tartaruga::retiraSoldados(int soldados) {

	this->quantSoldados -= soldados;

}
void Tartaruga::daMetade(int x, int y) {

	Navios *auxNavio = nullptr;
	auxNavio = mundo->getNavioXY(x, y);
	if (auxNavio->getNumSoldados() > 0) {
		//tira metade ao que da soldados e agua
		auxNavio->retiraAgua(auxNavio->getAgua() / 2);
		auxNavio->retiraSoldados(auxNavio->getNumSoldados() / 2);
		//fico com metade para mim  soldados e agua
		this->quantAgua = auxNavio->getAgua() / 2;
		this->quantSoldados = auxNavio->getNumSoldados() / 2;
	}
	else
		this->estado = aDeriva;
}
void Tartaruga::serConquistadoaDeriva() {

	int x = this->x, y = this->y;
	switch (mundo->verificaCelulaNavioPirata(x + 1, y)) {
	case CELULA_NAVIO_NORMAL:
		this->estado = normal;
		daMetade(x + 1, y);
		break;
	case CELULA_NAVIO_PIRATA:
		this->estado = afundado;
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
		this->estado = afundado;
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
		this->estado = afundado;
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
		this->estado = afundado;
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
		this->estado = afundado;
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
		this->estado = afundado;
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
		this->estado = afundado;
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
		this->estado = afundado;
		break;
	default:
		break;
	}

}
string Tartaruga::moveNavioAuto(int turnoAtual) {

	ostringstream os;

	unsigned int direcao;
	direcao = rand() % 9 + 1;
	this->moveNavio(direcao);

	switch (this->estado)
	{
	case autoMove:
		this->soldadosBebemAgua();
		os << this->combate(CELULA_NAVIO_PIRATA);
		break;


	}
	return os.str();
}
const int Tartaruga::sou()const {

	return TARTARUGA;

}
int Tartaruga::getMaxAgua() {
	return TARTARUGA_MAX__AGUA;
}
int Tartaruga::getMaxSoldados() {
	return TARTARUGA_MAX_SOLDADOS;
}
int Tartaruga::getAgua() {
	return this->quantAgua;
}

void Tartaruga::adicionaAgua(int agua) {
	this->quantAgua += agua;
}
string Tartaruga::acao(int xaAtacar, int yaAtacar) {

	ostringstream os;


	Navios *navioaAtacar = nullptr;
	navioaAtacar = mundo->getNavioXY(xaAtacar, yaAtacar);

	if (navioaAtacar != nullptr) {
		os << "---------------Combate------------------" << endl;

		os << "O navio com o ID: " << this->getId() << " mandou um petardo que o acertou no " << navioaAtacar->getId() << " e vai afundar" << endl;
		navioaAtacar->setEstado(afundado);

		os << "---------------Fim-Combate------------------" << endl;

		//num ataque destes os soldados ficaram com muita sede
		soldadosBebemAgua();
		soldadosBebemAgua();

		if (this->getAgua() <= 0)
			this->setNumSoldados(this->getNumSoldados() - 1);

		if (this->getAgua() <= 0 && this->getNumSoldados() <= 0)
			this->setEstado(afundado);

	}
	return os.str();
}
void Tartaruga::conquistaPorto(int xPorto, int yPorto) {

	char lastPortoAmigo = 'Z';

	// ultimo porto amigo
	lastPortoAmigo = mundo->LastPortoAmigo();
	//
	mundo->mudaPorto(xPorto, yPorto, lastPortoAmigo + 1);


}
void Tartaruga::conquistaPortoAmigo(int xPorto, int yPorto) {

	char lastPortoInimigo = 'z';

	// ultimo porto amigo
	lastPortoInimigo = mundo->LastPortoInimigo();
	//
	mundo->mudaPorto(xPorto, yPorto, lastPortoInimigo + 1);


}
string Tartaruga::acaoPortoAmigo() {

	ostringstream os;
	int sorteio = 0, soldadosPerdidos = 0;

	sorteio = randNumber(100);

	if (sorteio <= this->getNumSoldados()) {// o navio ganhou e conquista o porto
		soldadosPerdidos = (10 * this->getNumSoldados()) / 100;
		this->setNumSoldados(this->getNumSoldados() - soldadosPerdidos);

		//conquista Porto
		conquistaPortoAmigo(this->x, this->y);
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
string Tartaruga::acaoPorto() {

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
string Tartaruga::combate(int quemVouAtacar) {

	int xNavio = 0 , yNavio = 0;
	int aux = 10, encontrei = 0;
	
	do {

		xNavio = rand() % mundo->getDimX();
		yNavio = rand() % mundo->getDimY();

		if (mundo->verificaCelulaNavioPirata(xNavio, yNavio) == CELULA_NAVIO_PIRATA) {
			encontrei = 1;
			break;
		}

		aux--;
	} while (aux > 0);
		

	ostringstream os;
	if (encontrei == 1) {
		if (mundo->verificaCelulaNavioPirata(xNavio, yNavio) == quemVouAtacar && (!mundo->verificaCelulaNavioDeriva(xNavio, yNavio))) {
			os << acao(xNavio, yNavio);
		}
	}
	if (quemVouAtacar == CELULA_NAVIO_PIRATA) {//sou normal
		if (mundo->verificaCelulaPorto(xNavio, yNavio) == CELULA_PORTO_INIMIGO) {
			acaoPorto();
			os << "Porrada com o Porto Inimigo" << endl;
		}
	}

	if (quemVouAtacar == CELULA_NAVIO_NORMAL) {//sou pirata
		if (mundo->verificaCelulaPorto(xNavio, yNavio) == CELULA_PORTO_AMIGO) {
			acaoPortoAmigo();
			os << "Porrada com o Porto Inimigo" << endl;
		}
	}

	return os.str();
}
int Tartaruga::getMercadoriaNavio() const
{
	return 0;
}
void Tartaruga::setMercadoriaNavio(int quantCarga)
{
}
void Tartaruga::adicionaMercadoriaNavio(int quantCarga)
{
}
void Tartaruga::RetiraMercadoriaNavio(int quantCarga)
{
}
int Tartaruga::VerificaMaxMercadoria() const
{
	return 0;
}
int Tartaruga::getQuantidadePeixe() const
{
	return 0;
}
void Tartaruga::setQuantidadePeixe(int quantpeixe)
{
}
void Tartaruga::AdicionaQuantidadePeixe(int quantpeixe)
{
}
string Tartaruga::TrataNavioTempestade()
{
	ostringstream os;


	if (this->estado == pirata) {
		os << " O navio e do tipo Pirata e vai ser Afundado devido a ter sido apanhado por uma Tempestade ..!" << endl;
		this->estado = afundado;
	}
	else {
		os << " O navio e do tipo Normal e vai ser apanhado por uma Tempestade  ..!" << endl;
		if (rand() % 100 + 1 <= PROB_TARTARUGA_AFUNDAR_TEMPESTADE)
			this->estado = afundado;
		else {
			os << " O navio Resistiu a tempestade  e ira perder Soldados..!" << endl;
			this->quantSoldados = this->quantSoldados - ((quantSoldados * 15) / 100);

			AbasteceAguaNavio();
		}
	}
	return os.str();
}
int Tartaruga::FmoveEsquerda(int move) {
	int VerificaPorto = 0;

	if (x > 0 && (mundo->verificaCelulaMar(this->x - move, this->y) == CELULA_MAR) && (x - move >= 0)) {

		VerificaPorto = mundo->verificaCelulaPorto(this->x - move, this->y);

		if (VerificaPorto == CELULA_PORTO_AMIGO && mundo->verificaCelulaMar(this->x - 1, this->y) == CELULA_MAR) {// alterei aqui

			this->x = this->x - move;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO && mundo->verificaCelulaMar(this->x - 1, this->y) == CELULA_MAR) {

			if (mundo->verificaCelulaNavio(this->x - move, this->y) != CELULA_NAVIO && mundo->verificaCelulaNavio(this->x - 1, this->y) != CELULA_NAVIO && mundo->verificaCelulaMar(this->x - 1, this->y) == CELULA_MAR) {//alterei aqui

				this->x = this->x - move;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;

			}
		}
		if (VerificaPorto == CELULA_PORTO_INIMIGO && mundo->verificaCelulaMar(this->x - 1, this->y) == CELULA_MAR) {//alterei aqui
			this->x = this->x - move;
			return MOVE_VALIDO;
		}
	}
	else {

		if (x == 0 && (mundo->verificaCelulaMar(mundo->getDimX() - move, this->y) == CELULA_MAR)) {

			VerificaPorto = mundo->verificaCelulaPorto(mundo->getDimX() - move, this->y);

			if (VerificaPorto == CELULA_PORTO_AMIGO && mundo->verificaCelulaMar(this->x - 1, this->y) == CELULA_MAR) {//alterei aqui

				this->x = mundo->getDimX() - move;

				return MOVE_VALIDO;
			}
			if (VerificaPorto == CELULA_SEM_PORTO && mundo->verificaCelulaMar(this->x - 1, this->y) == CELULA_MAR) {//alterei aqui

				if (mundo->verificaCelulaNavio(mundo->getDimX() - move, this->y) != CELULA_NAVIO && mundo->verificaCelulaNavio(this->x - 1, this->y) != CELULA_NAVIO && mundo->verificaCelulaMar(this->x - 1, this->y) == CELULA_MAR) {//alterei aqui

					this->x = mundo->getDimX() - move;

					return MOVE_VALIDO;
				}
				else {

					return MOVE_INVALIDO;

				}
			}
			if (VerificaPorto == CELULA_PORTO_INIMIGO && mundo->verificaCelulaMar(this->x - 1, this->y) == CELULA_MAR) {// alterei aqui
				this->x = mundo->getDimX() - move;
				return MOVE_VALIDO;
			}
		}
	}
	return MOVE_INVALIDO;
}
int Tartaruga::FmoveDireita(int move) {
	int VerificaPorto = 0;
	//e ver se a nova pos está dentro de agua!
	if (x < mundo->getDimX() - 1 && (mundo->verificaCelulaMar(this->x + move, this->y) == CELULA_MAR) && (x + move) <= mundo->getDimX() - 1) {

		VerificaPorto = mundo->verificaCelulaPorto(this->x + move, this->y);

		if (VerificaPorto == CELULA_PORTO_AMIGO && mundo->verificaCelulaMar(this->x + 1, this->y) == CELULA_MAR) { //alterei aqui

			this->x = this->x + move;

			return MOVE_VALIDO;
		}
		if (VerificaPorto == CELULA_SEM_PORTO && mundo->verificaCelulaMar(this->x + 1, this->y) == CELULA_MAR) { //alterei aqui

			if (mundo->verificaCelulaNavio(this->x + move, this->y) != CELULA_NAVIO && mundo->verificaCelulaNavio(this->x + 1, this->y) != CELULA_NAVIO && mundo->verificaCelulaMar(this->x + 1, this->y) == CELULA_MAR) { //alterei aqui

				this->x = this->x + move;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;

			}
		}
		if (VerificaPorto == CELULA_PORTO_INIMIGO && mundo->verificaCelulaMar(this->x + 1, this->y) == CELULA_MAR) { //alterei aqui
			this->x = this->x + move;
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
int Tartaruga::FmoveCima(int move) {
	int VerificaPorto = 0;
	//e ver se a nova pos está dentro de agua!
	if (y > 0 && (mundo->verificaCelulaMar(this->x, this->y - move) == CELULA_MAR) && (y - move) >= 0) {


		VerificaPorto = mundo->verificaCelulaPorto(this->x, this->y - move);

		if (VerificaPorto == CELULA_PORTO_AMIGO && mundo->verificaCelulaMar(this->x, this->y - 1) == CELULA_MAR) { // alterei aqui

			this->y = this->y - move;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO) {

			if (mundo->verificaCelulaNavio(this->x, this->y - move) != CELULA_NAVIO && mundo->verificaCelulaNavio(this->x, this->y - 1) != CELULA_NAVIO && mundo->verificaCelulaMar(this->x, this->y - 1) == CELULA_MAR) {//alterei aqui

				this->y = this->y - move;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;

			}
		}

		if (VerificaPorto == CELULA_PORTO_INIMIGO && mundo->verificaCelulaMar(this->x, this->y - 1) == CELULA_MAR) { //alterei aqui
			this->y = this->y - move;
			return MOVE_VALIDO;
		}


	}
	else {

		if (y == 0 && (mundo->verificaCelulaMar(this->x, mundo->getDimY() - move) == CELULA_MAR) && mundo->verificaCelulaMar(this->x, this->y - 1) == CELULA_MAR) { //alterei aqui

			VerificaPorto = mundo->verificaCelulaPorto(this->x, mundo->getDimY() - move);

			if (VerificaPorto == CELULA_PORTO_AMIGO && mundo->verificaCelulaMar(this->x, this->y - 1) == CELULA_MAR) { //alterei aqui

				this->y = mundo->getDimY() - move;

				return MOVE_VALIDO;
			}

			if (VerificaPorto == CELULA_SEM_PORTO) {

				if (mundo->verificaCelulaNavio(this->x, mundo->getDimY() - move) != CELULA_NAVIO && mundo->verificaCelulaNavio(this->x, mundo->getDimY() - 1) != CELULA_NAVIO && mundo->verificaCelulaMar(this->x, this->y - 1) == CELULA_MAR) { //alterei aqui

					this->y = mundo->getDimY() - 1;

					return MOVE_VALIDO;

				}
				else {

					return MOVE_INVALIDO;
				}
			}
			if (VerificaPorto == CELULA_PORTO_INIMIGO && mundo->verificaCelulaMar(this->x, this->y - 1) == CELULA_MAR) {//alterei aqui
				this->y = mundo->getDimY() - move;
				return MOVE_VALIDO;
			}
		}
	}

	return MOVE_INVALIDO;
}
int Tartaruga::FmoveBaixo(int move) {
	int VerificaPorto = 0;
	//e ver se a nova pos está dentro de agua!
	if (y < mundo->getDimY() - 1 && (mundo->verificaCelulaMar(this->x, this->y + move) == CELULA_MAR) && (y + move) <= mundo->getDimY() - 1) {

		VerificaPorto = mundo->verificaCelulaPorto(this->x, this->y + move);

		if (VerificaPorto == CELULA_PORTO_AMIGO && mundo->verificaCelulaMar(this->x, this->y + 1) == CELULA_MAR) {//alterei aqui

			this->y = this->y + move;

			return MOVE_VALIDO;
		}

		if (VerificaPorto == CELULA_SEM_PORTO && mundo->verificaCelulaMar(this->x, this->y + 1) == CELULA_MAR) {//alterei aqui

			if (mundo->verificaCelulaNavio(this->x, this->y + move) != CELULA_NAVIO && mundo->verificaCelulaNavio(this->x, this->y + 1) != CELULA_NAVIO && mundo->verificaCelulaMar(this->x, this->y + 1) == CELULA_MAR) {//alterei aqui

				this->y = this->y + move;

				return MOVE_VALIDO;
			}
			else {

				return MOVE_INVALIDO;
			}
		}
		if (VerificaPorto == CELULA_PORTO_INIMIGO && mundo->verificaCelulaMar(this->x, this->y + 1) == CELULA_MAR) {//alterei aqui
			this->y = this->y + move;
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
int Tartaruga::FmoveCimaEsquerda(int move) {
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
int Tartaruga::FmoveCimaDireita(int move) {
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
int Tartaruga::FmoveBaixoEsquerda(int move) {
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
int Tartaruga::FmoveBaixoDireita(int move) {
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
int Tartaruga::moveNavio(int direcao, int turnoJogo) {

	unsigned int move = 0;
	move = rand() % 3;

	if (move == 1)
		move++;
	if (move == 0)
		move++;

	switch (direcao) {
	case moveEsquerda:
		if (FmoveEsquerda(move) == MOVE_VALIDO) {
			if (this->estado == normal)
				soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveDireita:
		if (FmoveDireita(move) == MOVE_VALIDO) {
			if (this->estado == normal)
				soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveCima:
		if (FmoveCima(move) == MOVE_VALIDO) {
			if (this->estado == normal)
				soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveBaixo:
		if (FmoveBaixo(move) == MOVE_VALIDO) {
			if (this->estado == normal)
				soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveCimaEsquerda:
		if (FmoveCimaEsquerda(move) == MOVE_VALIDO) {
			if (this->estado == normal)
				soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveCimaDireita:
		if (FmoveCimaDireita(move) == MOVE_VALIDO) {
			if (this->estado == normal)
				soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveBaixoEsquerda:
		if (FmoveBaixoEsquerda(move) == MOVE_VALIDO) {
			if (this->estado == normal)
				soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	case moveBaixoDireita:
		if (FmoveBaixoDireita(move) == MOVE_VALIDO) {
			if (this->estado == normal)
				soldadosBebemAgua();
			return MOVE_VALIDO;
		}
		else
			break;
	}
	return MOVE_INVALIDO;
}
Tartaruga::~Tartaruga()
{
}
