#include "Mundo.h"
#include "Jogador.h"

using namespace std;

int Mundo::portosBemColocado() {


	for (unsigned int i = 0; i < porto.size(); i++) {
		
		int xPorto = porto[i]->getX(), yPorto = porto[i]->getY();
		int celulasTerra = 0;
					
			for (unsigned t = 0; t < superficie.size() ;t++){
				
				if(superficie[t]->VerificaCelulaTerra() == true){

					if ((superficie[t]->getX() == xPorto-1) && (superficie[t]->getY()==yPorto)) { //esquerda
						celulasTerra++;
					}
					if ((superficie[t]->getX() == xPorto + 1) && (superficie[t]->getY() == yPorto)) { //direita
						celulasTerra++;
					}
					if ((superficie[t]->getX() == xPorto) && (superficie[t]->getY() == yPorto+1)) { //baixo
						celulasTerra++;
					}
					if ((superficie[t]->getX() == xPorto) && (superficie[t]->getY() == yPorto-1)) { //cima
						celulasTerra++;
					}
			
				}
			}
			if (celulasTerra == 0) {
				return 0;
			}
	}
	return 1;
}
void Mundo::abasteceNaviosNosPortos() {


	for (unsigned int i = 0; i < porto.size(); i++) {
		for (unsigned int j = 0; j < navios.size();j++) {
			if ((navios[j]->getEstado() == normal || navios[j]->getEstado() == autoMove || navios[j]->getEstado() == vaiPara) && (navios[j]->getX() == porto[i]->getX()) && (navios[j]->getY() == porto[i]->getY())) {
				
				if (porto[i]->verificaPortoAmigo()==true) {
					if (navios[j]->sou() == FRAGATA) {
						navios[j]->AbasteceAguaNavio();
					}
					if (navios[j]->sou() == VELEIRO) {
						navios[j]->AbasteceAguaNavio();
					}
					if (navios[j]->sou() == GALEAO) {
						navios[j]->AbasteceAguaNavio();
					}
					if (navios[j]->sou() == ESCUNA) {
						navios[j]->AbasteceAguaNavio();
					}
				}
			}
		}
	}


}

void Mundo::verificaaDeriva() {
	
	for (unsigned int i = 0; i < navios.size(); i++) {
		if (navios[i]->getEstado() == aDeriva) {
			navios[i]->serConquistadoaDeriva();
		}
	}


}

void Mundo::mudaPorto(int xPorto,int yPorto,char letra) {

	for (unsigned int i = 0; i < porto.size(); i++) {
		if (porto[i]->getX() == xPorto && porto[i]->getY() == yPorto) {
			porto[i]->MudaTipoPorto(letra);
		}

	}

}
char Mundo::LastPortoAmigo() {

	char primeiroMaior ='A';

	for (unsigned int i = 0; i < porto.size(); i++) {


		if (porto[i]->getChar() >= 'A' && porto[i]->getChar() <= 'Z') {//se for amigo
			if (porto[i]->getChar() > primeiroMaior) {//se a letra que eu estou a ver agora for maior que a primeriaMaior
				primeiroMaior = porto[i]->getChar();//substituo
			}
		}
	}

	return primeiroMaior;
	
}
char Mundo::LastPortoInimigo() {

	char primeiroMaior = 'a';

	for (unsigned int i = 0; i < porto.size(); i++) {


		if (porto[i]->getChar() >= 'a' && porto[i]->getChar() <= 'z') {//se for amigo
			if (porto[i]->getChar() > primeiroMaior) {//se a letra que eu estou a ver agora for maior que a primeriaMaior
				primeiroMaior = porto[i]->getChar();//substituo
			}
		}
	}

	return primeiroMaior;

}
int Mundo::ValidaTipoNavio(const char tipo) {
	if (tipo == 'F')
		return FRAGATA;
	else if( tipo  == 'V')
		return VELEIRO;
	else if (tipo == 'E')
		return ESCUNA;
	else if (tipo == 'T')
		return TARTARUGA;
	else
		return GALEAO;
}
int Mundo::ValidaTipoNavioP(const char tipo) {
	if (tipo == 'F')
		return FRAGATA;
	else
		return VELEIRO;
}
int Mundo::verificaCelulaMar(int x, int y) {

	for (unsigned int i = 0; i < this->superficie.size(); i++) {
		if (this->superficie[i]->getX() == x && this->superficie[i]->getY() == y) {
			if (superficie[i]->VerificaCelulaMar() == false){
				return CELULA_TERRA;
			}
		}

	}
	return CELULA_MAR;
}
int Mundo::verificaCelulaNavio(int x, int y) {

	for (unsigned int i = 0; i < this->navios.size(); i++) {
		if (navios[i]->getX() == x && navios[i]->getY() == y)
			return CELULA_NAVIO;
	}

	return 0;
}
int Mundo::verificaCelulaNavioPirata(int x, int y) {

	for (unsigned int i = 0; i < this->navios.size(); i++) {
		if (navios[i]->getX() == x && navios[i]->getY() == y) {
			if (navios[i]->getEstado()==pirata) {
				return CELULA_NAVIO_PIRATA;
			}
			else
				return CELULA_NAVIO_NORMAL;
		}
	}

	return 0;
}
int Mundo::verificaCelulaNavioDeriva(int x, int y) {

	for (unsigned int i = 0; i < this->navios.size(); i++) {
		if (navios[i]->getX() == x && navios[i]->getY() == y) {
			if (navios[i]->getEstado() == aDeriva) {
				return true;
			}
			else
				return false;
		}
	}

	return 0;
}

Navios & Mundo::criaNavio(Mundo *mundo,const char portoPrincipal, const char TipoNavio) {

	unsigned int x=0, y=0;
	Navios *aux;
	for (unsigned int i = 0; i < porto.size(); i++) {

		if (porto[i]->getChar() == portoPrincipal) {

			x = porto[i]->getX();

			y = porto[i]->getY();
		}
	}
	
	switch (ValidaTipoNavio(TipoNavio))
	{
		case VELEIRO:
			//Navios(Mundo *mundo, char tipo, int x, int y, int quantSoldados, int quantAgua = 0, int estado=normal);
			aux = new Veleiro(mundo,x, y,autoMove);
			break;
		case GALEAO:
			aux = new Galeao(mundo, x, y, autoMove);
			break;
		case ESCUNA:
			aux = new Escuna(mundo, x, y, autoMove);
			break;
		case FRAGATA:
			aux = new Fragata(mundo, x, y, autoMove	);
			break;
		case TARTARUGA:
			aux = new Tartaruga(mundo, x, y, autoMove);
			break;
	}
	
	this->navios.push_back(aux);

	return *aux;
}
string Mundo::moveNavioPirataAuto() {

	ostringstream os;

	for (unsigned int i = 0; i < navios.size(); i++) {
		cout << "navio: " << navios[i]->getId() << " soldados: " << navios[i]->getNumSoldados() << " agua " << navios[i]->getAgua() << endl;
		if (navios[i]->getEstado()== pirata) {

				unsigned int direcao;

				direcao = rand() % 9 + 1;

				this->navios[i]->moveNavio(direcao);
				
				os<<this->navios[i]->combate(CELULA_NAVIO_NORMAL); //O TIPO DE NAVIO QUE SE QUER ATACAR!
			
		}
	}
	return os.str();
}
Navios * Mundo::criaNavPirata(Mundo *mundo, const char TipoNavio,int x,int y) {

	//pirata
	Navios *aux=nullptr;
	
	switch (ValidaTipoNavioP(TipoNavio))
	{
	case VELEIRO:
		aux = new Veleiro(mundo, x, y, pirata);
		break;
	case FRAGATA:
		aux = new Fragata(mundo,x, y,pirata);
		break;
	}


	this->navios.push_back(aux);

	return aux;
}
const char Mundo::getPortoPrincipal() {

	for (unsigned int i = 0; i < porto.size(); i++) {

		if (porto[i]->getChar() >= 'A' && porto[i]->getChar() <= 'Z') {

			return porto[i]->getChar();

		}	
	}
	return '-';

}
void Mundo::criaSuperficie(int x, int y, char tipo) {

	if (tipo == '+')
		superficie.push_back(new Terra(x, y));
	else
		superficie.push_back(new Mar(x, y));
}

void Mundo::criaCelulaPorto(int x, int y,char t)
{

	this->porto.push_back(new Porto(x, y, t));

}

void Mundo::retiraNavAfundados() { // NAO FAÇO IDEIA O QUE FIZ AQUI FRIAS .. SEM QUE TEM HAVER COM A CENA DE APAGAR UMA COISA ENQUANTO ESTAMOS A PERCORRER A MESMA

	for (auto it = navios.begin(); it != navios.end();) {

		if ((*it)->getEstado() == afundado) {
			cout << "morreu navio: " << (*it)->getId()<<endl;
			delete *it;
			it = navios.erase(it);
		}
		else
			++it;
	}
}


const vector<const Superficie*> Mundo::getVetorSuperficie() const
{
	return vector<const Superficie*>(this->superficie.begin(), this->superficie.end());
}

const vector<const Porto*> Mundo::getVetorPorto() const
{
	return vector<const Porto *>(this->porto.begin(), this->porto.end());
}
const vector<const Navios*> Mundo::getVetorNavios() const
{
	return vector<const Navios *>(this->navios.begin(), this->navios.end());
}

Navios * Mundo::getNavio(int id) {

	for (unsigned int i = 0; i < navios.size(); i++)
		if (navios[i]->getId() == id)
			return navios[i];

	return nullptr;
}
Porto * Mundo::getPorto(char tipo) {

	for (unsigned int i = 0; i < porto.size(); i++)
		if (porto[i]->getChar() == tipo)
			return porto[i];

	return nullptr;
}
Navios * Mundo::getNavioXY(int x,int y) {

	for (unsigned int i = 0; i < navios.size(); i++)
		if (navios[i]->getX() == x && navios[i]->getY() == y)
			return navios[i];

	return nullptr;
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
bool Mundo::getExistenciaEvento() const
{
	return this->EstadoEvento;
}
void Mundo::setExistenciaEvento(bool estado)
{
	this->EstadoEvento = estado;
}
void Mundo::setEventoEmExecucao(Eventos * evento)
{
	this->Evento = evento;
}
string Mundo::TrataEventoMotim(int estadoMotim, int modoExecucao, int idNavio) {

	ostringstream os;

	static int indice, estado;

	if (estadoMotim == MOTIM_ESTADO_INICIO_MOTIM){

		if (navios.size() > 0 && this->VerificaExistenciaNavios() == true) {
			
			if (modoExecucao != EVENTO_EXECUCAO_COMANDO) {

				do {

					indice = rand() % navios.size();

					if (navios[indice]->getEstado() == normal || navios[indice]->getEstado() == pirata || navios[indice]->getEstado() == autoMove)
						break;

				} while (navios[indice]->getEstado() != normal || navios[indice]->getEstado() != pirata || navios[indice]->getEstado() != autoMove);
			}
			else {
				for (int i = 0; i < navios.size(); i++) {
					if (navios[i]->getEstado() == normal || navios[i]->getEstado() == pirata || navios[i]->getEstado() == autoMove)
						if (navios[i]->getId() == idNavio && navios[i] != nullptr){
							indice = i;
							break;
					}
				}
			}
	
			os << " O navio com o ID" << navios[indice]->getId() << "foi apanhado por 1 Motim" << endl;
					
			// so navio for apanhado por 1 motim,  e for pirata fica á deriva
			if (navios[indice]->getEstado() == pirata) {
					
				os << " Os Piratas Foram tomar Banho, o Navio irá ficar á deriva Temporariamente ..!" << endl;
				
				estado = navios[indice]->getEstado();

				navios[indice]->setEstado(aDeriva);

			} // se o navio for apanhado por 1 motim e for do jogador fica em modo pirata
			else if (navios[indice]->getEstado() == normal || navios[indice]->getEstado() == autoMove) {
					
				os << " O NAvio do Jogador vai se tornar Pirata Temporariamente " << endl;
				
				estado = navios[indice]->getEstado();

				navios[indice]->setEstado(pirata);
			}
				
		}
		else
			os << " Não Existem Navios para ser realizado o Motim no Mundo" << endl;
	}
	else {
		
		navios[indice]->setEstado(estado);

	}

	return os.str();
}
string Mundo::TrataEventoCalmaria(int epiX, int epiY, int estado) {

	ostringstream os;

	static vector < int> Calmaria;
	static vector < int > EstadoAntigo;

	int x, y;

	if (estado == CALMARIA_ESTADO_EM_EXECUCAO_CALMARIA) {
		if (navios.size() > 0) {
			for (unsigned int s = 0; s < navios.size(); s++) {

				x = navios[s]->getX();

				y = navios[s]->getY();

				if (x >= (epiX - RANGE_EVENTO) && x <= (epiX + RANGE_EVENTO) && y >= (epiY - RANGE_EVENTO) && y <= (epiY + RANGE_EVENTO)) {

					os << " Foi Encontrado um Navio com o id " << navios[s]->getId() << " na posicao [ " << x << " : " << y << " ] " << endl;

					os << " O navio com o Id " << navios[s]->getId() << " : Vai ser afetado por uma calmaria" << endl;

					os << " O estado antigo do Navio com o ID " << navios[s]->getId() << "era : " << navios[s]->getEstado() << "  .. !" << endl;

					if (navios[s]->getEstado() != calmaria && navios[s]->getEstado() != afundado) {

						Calmaria.push_back(navios[s]->getId());

						EstadoAntigo.push_back(navios[s]->getEstado());

						navios[s]->setEstado(calmaria);
					}

				}
			}
		}
		else
			os << " Não Existem Navios no Mundo..!" << endl;

	}
	else {
		if (navios.size() > 0  && Calmaria.size() > 0 ){
			for (unsigned int k = 0; k < Calmaria.size(); k++) {
				for (unsigned int j = 0; j < navios.size();j++) {
					if (Calmaria[k] == navios[j]->getId() && navios[j] != nullptr){
						navios[j]->setEstado(EstadoAntigo[k]);
					}
				}
			}
			Calmaria.erase(Calmaria.begin(), Calmaria.end());

			EstadoAntigo.erase(EstadoAntigo.begin(), EstadoAntigo.end());
		}
	}
	return os.str();
}
string Mundo::TrataEventoSereias(int indice) {

	ostringstream os;
	
	os << navios[indice]->AlteraSoldadosPosEvento(PROB_SEREIAS_AFETAR_SOLDADOS);

	return os.str();

}
string Mundo::TrataEventoTempestade(int epiX, int epiY)
{
	ostringstream os;

	int x, y;

	for(int i = 0; i < navios.size(); i++ ){

		x = navios[i]->getX();

		y = navios[i]->getY();

		if (x >= (epiX - RANGE_EVENTO) && x <= (epiX + RANGE_EVENTO) && y >= (epiY - RANGE_EVENTO) && y <= (epiY + RANGE_EVENTO)) {

			os << " O Navio com o id   " << navios[i]->getId() << "   na posicao [ " << x << " : " << y << " ] " << endl;

			os << navios[i]->TrataNavioTempestade() << endl;
		}

	}
	return os.str();
}
// por defeito o tipo de eventos vai ter valor 0 para entrar no default e executar a acao para eventos que duram mais do que 1 turno
string Mundo::trataEventos(int modoExecucao, int TipoEvento, int idNavio, int coordX, int coordY)
{
	ostringstream os;

	int epicentroX, epicentroY, indice = 0;

	switch (TipoEvento)
	{
	case EVENTO_TEMPESTADE:

		if ( modoExecucao != EVENTO_EXECUCAO_COMANDO){

			epicentroX = rand() % ((this->dimY -2) - 2)+2;
			
			epicentroY = rand() % ((this->dimX - 2) - 2 )+2;
		
		}
		else {

			epicentroX = coordX;

			epicentroY = coordY;

		}
		os << " <<<<      Epicentro da Tempestade:  [ " << epicentroX << " : " << " ]     >>>>" << epicentroY << endl;
		
		os << TrataEventoTempestade(epicentroX, epicentroY);

		this->EstadoEvento = EVENTO_OFF;

		return os.str();

		break;

	case EVENTO_SEREIAS:
		
		if (navios.size() > 0) {

			for (int i = 0; i < navios.size(); i++) {
				
				if (navios[i]->getEstado() == normal || navios[i]->getEstado() == pirata || navios[i]->getEstado() == autoMove) {

					if (modoExecucao != EVENTO_EXECUCAO_COMANDO) {
					
						do {

							indice = rand() % navios.size();
							

						} while (navios[indice]->getEstado() != normal && navios[indice]->getEstado() != pirata && navios[indice]->getEstado() != autoMove);
						
						break;
					}
					else {

						if (navios[i]->getId() == idNavio && navios[i] != nullptr){
						
							indice = i;
						
							break;
						}
					}
				}
			}
			
			if (navios[indice]->getNumSoldados() > 0 && navios[indice] != nullptr) {

				os << " Navio com o ID :  " << navios[indice]->getId() << "  vai sofrer ataque de sereia" << endl;

				os << TrataEventoSereias(indice);

			}				
		}
		else
			os <<" Nao existem navios para efetuar o ataque da sereia  ...!" << endl;

		this->EstadoEvento = EVENTO_OFF;

		return os.str();
		
		break;

	default:

		if (Evento != nullptr && Evento->getTTL() > 0){

			if (this->VerificaTipoEventoEmExecucao() == true)
				os << Evento->TrataEvento(modoExecucao, idNavio, coordX, coordY, TTL_CALMARIA);
			else
				os << Evento->TrataEvento(modoExecucao, idNavio, coordX, coordY, TTL_MOTIM);

			if (Evento->getTTL() == 0) {

				this->EstadoEvento = EVENTO_OFF;

			}
		}
			return os.str();

			break;
	}	
	return os.str();
}
// vai criar os eventos que duram mais que 1 turno;
string Mundo::criaEvento(Mundo * mundo, int tipo)
{
	ostringstream os;

	switch (tipo)
	{
	case EVENTO_CALMARIA:

		this->Evento = new Calmaria(mundo);
		this->EstadoEvento = EVENTO_ON;
		break;

	case EVENTO_MOTIM:
		this->Evento = new Motim(mundo);
		this->EstadoEvento = EVENTO_ON;
		break;
	}
	return os.str();
}
bool  Mundo::VerificaExistenciaNavios()
{
	if (navios.size() > 0)
		for (auto it = navios.begin(); it != navios.end();){
			if ((*it)->getEstado() == normal || (*it)->getEstado() == pirata || (*it)->getEstado() == autoMove)
				return true;
			++it;
		}

		return false;
}
void Mundo::limpaVetores() {

	superficie.clear();
	porto.clear();
	navios.clear();

}
int Mundo::verificaCelulaPorto(int x, int y) {
	
	for (unsigned int i = 0; i < this->porto.size(); i++) {
		if (porto[i]->getX() == x && porto[i]->getY() == y) {
			if (porto[i]->verificaPortoAmigo() == true)
				return CELULA_PORTO_AMIGO;
			else
				return CELULA_PORTO_INIMIGO;
		}
	}
	return CELULA_SEM_PORTO;
}


Mundo::~Mundo(){

	for (Superficie *superficie : superficie)
		delete superficie;

	for (Porto *portos : porto)
		delete portos;
	
	for (Navios *navios : navios)
		delete navios;

}
