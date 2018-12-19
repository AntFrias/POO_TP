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
void Mundo::bebemTodosAgua() {

	for (unsigned int i = 0; i < navios.size(); i++) {

		if (navios[i]->souPirata() != true) {
			navios[i]->soldadosBebemAgua();
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
int Mundo::ValidaTipoNavio(const char tipo) {
	if (tipo == 'F')
		return FRAGATA;
	else if( tipo  == 'V')
		return VELEIRO;
	else if (tipo == 'E')
		return ESCUNA;
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
			if (navios[i]->souPirata()) {
				return CELULA_NAVIO_PIRATA;
			}
			else
				return CELULA_NAVIO_NORMAL;
		}
	}

	return 0;
}

Navios & Mundo::criaNavio(Mundo *mundo,const char portoPrincipal, const char TipoNavio) {

	int x, y;
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
			aux = new Veleiro(mundo,false,false,x, y);
			break;
		case GALEAO:
			aux = new Galeao(mundo,false,false,x, y);
			break;
		case ESCUNA:
			aux = new Escuna(mundo, false,false,x, y);
			break;
		case FRAGATA:
			aux = new Fragata(mundo,false,false,x, y);
			break;
	}
	
	this->navios.push_back(aux);

	return *aux;
}
void Mundo::moveNavioPirataAuto() {

	for (unsigned int i = 0; i < navios.size(); i++) {
		if (navios[i]->souPirata()== true) {
			if (navios[i]->getAutoMove() == 1) {

				unsigned int direcao;

				direcao = rand() % 9 + 1;

				this->navios[i]->moveNavio(direcao);
				this->navios[i]->combate(); //aqui
			}
		}
	}
}
void Mundo::criaNavPirata(Mundo *mundo, const char TipoNavio,int x,int y) {

	//pirata
	Navios *aux=nullptr;
	
	switch (ValidaTipoNavioP(TipoNavio))
	{
	case VELEIRO:
		aux = new Veleiro(mundo, true, true, x, y);
		break;
	case FRAGATA:
		aux = new Fragata(mundo, true,true, x, y);
		break;
	}


	this->navios.push_back(aux);

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

		if ((*it)->getAfundado() == true) {

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
string Mundo::TrataEventoSereias(int indice) {

	ostringstream os;
	
	os << navios[indice]->AlteraSoldadosPosEvento(PROB_SEREIAS_AFETAR_SOLDADOS);

	return os.str();

}
string Mundo::TrataEventoTempestade(int epiX, int epiY)
{
	ostringstream os;

	int x, y;

	for (auto it = navios.begin(); it != navios.end();) {

		x = (*it)->getX();

		y = (*it)->getY();

		if (x >= (epiX - RANGE_TEMPESTADE) && x <= (epiX + RANGE_TEMPESTADE) && y >= (epiY - RANGE_TEMPESTADE) && y <= (epiY + RANGE_TEMPESTADE)) {

			os << "Foi Encontrado um Navio com o id " << (*it)->getId() << "na posicao " << x << " , " << y << endl;

			(*it)->TrataNavioTempestade();
		}
		++it;
	}
	return os.str();
}
// por defeito o tipo de eventos vai ter valor 0 para entrar no default e executar a acao para eventos que duram mais do que 1 turno
string Mundo::TrataEventos(int TipoEvento)
{
	ostringstream os;

	int epicentroX, epicentroY, indice;

	switch (TipoEvento)
	{
	case EVENTO_TEMPESTADE:

		do {

			epicentroX = rand() % this->dimX + 1;
			
			epicentroY = rand() % this->dimY + 1;
		
		} while (epicentroX >= 0 + 2 && epicentroX < this->dimX - 3 && epicentroX >= 0 + 2 && epicentroY <= this->dimY - 3);

		os << "Vai ser gerada uma tempestade nas coordenadas: " << epicentroX << ", " << epicentroY << endl;
		
		TrataEventoTempestade(epicentroX, epicentroY);

		this->EstadoEvento = EVENTO_OFF;

		// executa codigo para a tempestade
		break;
	case EVENTO_SEREIAS:
		
		if (navios.size() > 0) {

			indice = rand() % navios.size();
			
			if ( navios[indice]->getNumSoldados() > 0){
				
				os << "Navio com o ID : " << navios[indice]->getId() << " vai sofrer ataque de sereia" << endl;
				
				os << TrataEventoSereias(indice);

				return os.str();

			}
			else {

				os << "O navio com o ID " << navios[indice]->getId() << "nao tem soldados " << endl;
				
				return os.str();
			
			}
		}
		else
			os <<"Nao existem navios para efetuar o ataque da sereia" << endl;

		this->EstadoEvento = EVENTO_OFF;

		return os.str();
		
		break;

	default:

		if (Evento->ValidaEventoCalmaria() == true)
			Evento->TrataEvento();
		else
			Evento->TrataEvento();
		
		break;
	}	
	return os.str();
}
// vai criar os eventos que duram mais que 1 turno;
void Mundo::criaEvento(Mundo * mundo, int tipo)
{
	switch (tipo)
	{
	case EVENTO_CALMARIA:
		this->Evento = new Calmaria(mundo);
		TrataEventos(EVENTO_CALMARIA);
		break;
	case EVENTO_MOTIM:
		this->Evento = new Motim(mundo);
		TrataEventos(EVENTO_MOTIM);
		break;
	}

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
