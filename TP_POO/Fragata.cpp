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
		if (this->quantSoldados <= 0) {
			this->estado = aDeriva;
		}
	}

}
void Fragata::retiraAgua(int agua) {

	this->quantAgua -= agua;

}
void Fragata::retiraSoldados(int soldados) {

	this->quantSoldados -= soldados;

}
void Fragata::daMetade(int x, int y) {

	Navios *auxNavio = nullptr;
	auxNavio = mundo->getNavioXY(x,y);
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
void Fragata::serConquistadoaDeriva() {

	int x = this->x, y = this->y;
	switch (mundo->verificaCelulaNavioPirata(x + 1, y)){
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
string Fragata::moveNavioAuto(int turnoAtual) {

	ostringstream os;


	
	if (this->getEstado() == autoMove) {
		const vector <const Navios *>  auxNavio = mundo->getVetorNavios();

		for (unsigned int i = 0; i < auxNavio.size(); i++) {//ver se ha algum navio inimigo e deslocarme para o atacar

			if (auxNavio[i]->getEstado() == pirata) {
				mundo->setVaiPara(this->getId(),auxNavio[i]->getX(), auxNavio[i]->getY());
				break;
			}

		}//percorri os navios todos e nao h� nenhum pirata

		for (unsigned int i = 0; i < auxNavio.size(); i++) {//vou ficar perto de uma escuna ou galeao
			if (auxNavio[i]->sou() == ESCUNA || auxNavio[i]->sou() == GALEAO) {
				mundo->setVaiPara(this->getId(), auxNavio[i]->getX(), auxNavio[i]->getY());
				break;
			}
		}//senao ouver pirata nem escuna ou galeao para proteger anda aleatoriamente

	}

	unsigned int direcao;
	direcao = rand() % 9 + 1;
	this->moveNavio(direcao);

	switch (this->estado) 
	{
		case autoMove:
			this->soldadosBebemAgua();
			os << this->combate(CELULA_NAVIO_PIRATA);
			break;

		case pirata: 
			os<< this->combate(CELULA_NAVIO_NORMAL);
			break;

	}
	return os.str();
}
const int Fragata::sou()const{

	return FRAGATA;

}
int Fragata::getMaxAgua() {
	return FRAGATA_MAX_AGUA;
}
int Fragata::getMaxSoldados() {
	return FRAGATA_MAX_SOLDADOS;
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
	if (navioaAtacar != nullptr) {
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
			this->quantSoldados -= soldadosPerdidos;// este perdeu 20% da sua popula��o
			navioaAtacar->setNumSoldados(navioaAtacar->getNumSoldados() - (soldadosPerdidos * 2));// o outro perde 2 vezes mais que o outro


			if (navioaAtacar->getNumSoldados() <= 0) {
				//set afundado
				navioaAtacar->setEstado(afundado);
				//passar a metade da carga
				//-> Fragata n�o tem carga n passa nada
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
			navioaAtacar->setNumSoldados(navioaAtacar->getNumSoldados() - soldadosPerdidos);// o atacado perde 20% da sua popula��o
			this->quantSoldados -= soldadosPerdidos * 2; //este perde 2 vezes mais que o outro

			if (this->quantSoldados <= 0) {
				//set afundar 
				this->estado = afundado;
				//passar a metade da carga
				//-> Fragata n�o tem carga n passa nada
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
		os << "-------------Fim_Combate----------------" << endl << endl;
	}
	return os.str();
}
void Fragata::conquistaPorto(int xPorto,int yPorto) {
	
	char lastPortoAmigo = 'Z';

	// ultimo porto amigo
	lastPortoAmigo=mundo->LastPortoAmigo();
	//
	mundo->mudaPorto(xPorto, yPorto,lastPortoAmigo+1);


}
void Fragata::conquistaPortoAmigo(int xPorto, int yPorto) {

	char lastPortoInimigo = 'z';

	// ultimo porto amigo
	lastPortoInimigo = mundo->LastPortoInimigo();
	//
	mundo->mudaPorto(xPorto, yPorto, lastPortoInimigo + 1);


}
string Fragata::acaoPortoAmigo() {

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
int Fragata::getMercadoriaNavio() const
{
	return 0;
}
void Fragata::setMercadoriaNavio(int quantCarga)
{

}
void Fragata::adicionaMercadoriaNavio(int quantCarga)
{
}
void Fragata::RetiraMercadoriaNavio(int quantCarga)
{
}
int Fragata::VerificaMaxMercadoria()const
{
	return FRAGATA_QUANT_MAX_CARGA;
}
int Fragata::getQuantidadePeixe() const
{
	return 0;
}
void Fragata::setQuantidadePeixe(int quantpeixe)
{
}
void Fragata::AdicionaQuantidadePeixe(int quantpeixe)
{
}
string Fragata::combate(int quemVouAtacar) {

	int xNavio = getX(), yNavio = getY();
	ostringstream os;

		if (mundo->verificaCelulaNavioPirata(xNavio + 1, yNavio) == quemVouAtacar && ( !mundo->verificaCelulaNavioDeriva(xNavio + 1, yNavio) ) ) {
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
string Fragata::TrataNavioTempestade()
{
	ostringstream os;

	
	if (this->estado == pirata) {
		os << " O navio e do tipo Pirata e vai ser Afundado devido a ter sido apanhado por uma Tempestade ..!" << endl;
		this->estado = afundado;
	}
	else {
		os << " O navio e do tipo Normal e vai ser apanhado por uma Tempestade  ..!" << endl;
		if (rand() % 100 + 1 <= PROB_FRAGATA_AFUNDAR_TEMPESTADE)
			this->estado = afundado;
		else {
			os << " O navio Resistiu a tempestade  e ira perder Soldados..!" << endl;
			this->quantSoldados = this->quantSoldados - ((quantSoldados * 15) / 100);
		
			AbasteceAguaNavio();
		}
	}
	return os.str();
}
int Fragata::FmoveEsquerda(int move) {
	int VerificaPorto = 0;
	
	if (x > 0 && (mundo->verificaCelulaMar(this->x - move, this->y) == CELULA_MAR) && (x - move>=0) ) {

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
int Fragata::FmoveDireita(int move) {
	int VerificaPorto = 0;
	//e ver se a nova pos est� dentro de agua!
	if (x < mundo->getDimX() - 1 && (mundo->verificaCelulaMar(this->x + move, this->y) == CELULA_MAR)&& (x+move) <= mundo->getDimX()-1 ) {

		VerificaPorto = mundo->verificaCelulaPorto(this->x + move, this->y);

		if (VerificaPorto == CELULA_PORTO_AMIGO && mundo->verificaCelulaMar(this->x+1, this->y) == CELULA_MAR) { //alterei aqui

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
int Fragata::FmoveCima(int move) {
	int VerificaPorto = 0;
	//e ver se a nova pos est� dentro de agua!
	if (y > 0 && (mundo->verificaCelulaMar(this->x, this->y - move) == CELULA_MAR) && (y-move)>=0) {


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
int Fragata::FmoveBaixo(int move) {
	int VerificaPorto = 0;
	//e ver se a nova pos est� dentro de agua!
	if (y < mundo->getDimY() - 1 && (mundo->verificaCelulaMar(this->x, this->y + move) == CELULA_MAR) && (y+move)<=mundo->getDimY()-1) {

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
int Fragata::FmoveCimaEsquerda(int move) {
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
	////encostado � esquerda
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
int Fragata::FmoveCimaDireita(int move) {
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
	//encostado � direita
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
int Fragata::FmoveBaixoEsquerda(int move) {
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
	//////encostado � esquerda
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
int Fragata::FmoveBaixoDireita(int move) {
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
	////////encostado � direita
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
int Fragata::moveNavio(int direcao, int turnoJogo) {
		
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
Fragata::~Fragata()
{
}
