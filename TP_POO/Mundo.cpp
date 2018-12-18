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

		navios[i]->soldadosBebemAgua();

	}


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
			aux = new Veleiro(mundo, x, y);
			break;
		case GALEAO:
			aux = new Galeao(mundo, x, y);
			break;
		case ESCUNA:
			aux = new Escuna(mundo, x, y);
			break;
		case FRAGATA:
			aux = new Fragata(mundo, x, y);
			break;
	}
	
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
void Mundo::TrataEventoSereias(int indice) {

	this->navios[indice]->setNumSoldados((this->navios[indice]->getNumSoldados() * 10) / 100);

}
void Mundo::TrataEventoTempestade(int x, int y)
{
	int QuantCargaPerder, probAfundar;

	for (auto it = navios.begin(); it != navios.end();) {
		
		if (x >= (*it)->getX() -2 && x <= (*it)->getX() + 2 && y >= (*it)->getY() - 2 && y <= (*it)->getY() - 2 ) {
			
			switch ((*it)->sou()) {
				
			case FRAGATA:

				if (rand() % 100 + 1 <= PROB_FRAGATA_AFUNDAR_TEMPESTADE) 
					(*it)->setAfundado(NAVIO_AFUNDADO);
				
				(*it)->setNumSoldados(((*it)->getNumSoldados()*15)/100);
				
				(*it)->AbasteceAguaNavio();

				break;

			case ESCUNA:
				
				QuantCargaPerder = rand() % 100 + 1;

				probAfundar = rand() % 100 + 1;
				
				if (probAfundar > PROB_ESCUNA_AFUNDAR_TEMPESTADE && QuantCargaPerder <= PROB_ESCUNA_PERDER_CARGA)
					(*it)->RetiraCargaNavio(QuantCargaPerder);

				else if (probAfundar <= PROB_ESCUNA_AFUNDAR_TEMPESTADE)
					(*it)->setAfundado(NAVIO_AFUNDADO);

				(*it)->setNumSoldados(((*it)->getNumSoldados() * 15) / 100);

				(*it)->AbasteceAguaNavio();

				break;

			case VELEIRO:

				QuantCargaPerder = rand() % 100 + 1;

				probAfundar = rand() % 100 + 1;

				if (probAfundar > PROB_VELEIRO_AFUNDAR_TEMPESTADE_1 && QuantCargaPerder >= PROB_VELEIRO_PERDER_CARGA)
					(*it)->RetiraCargaNavio(QuantCargaPerder);
				
				else if (probAfundar <= PROB_VELEIRO_AFUNDAR_TEMPESTADE_2) // aqui a probabilidade é diferente pelo facto do 
					(*it)->setAfundado(NAVIO_AFUNDADO);						//navio pedir apenas 20% de prob caso tenha menos que 50%
						    												// de capacidade de carga

				(*it)->AbasteceAguaNavio();
				break;
			case GALEAO:

				probAfundar = rand() % 100 + 1;

				if (probAfundar <= PROB_GALEAO_AFUNDAR_TEMPESTADE) // aqui a probabilidade é diferente pelo facto do 
					(*it)->setAfundado(NAVIO_AFUNDADO);

				(*it)->setNumSoldados(((*it)->getNumSoldados() * 10) / 100);

				(*it)->AbasteceAguaNavio();

				break;

			}
		}	
		++it;
	}
}
// por defeito o tipo de eventos vai ter valor 0 para entrar no default e executar a acao para eventos que duram mais do que 1 turno
void Mundo::TrataEventos(int TipoEvento)
{
	int epicentroX, epicentroY, indice;

	switch (TipoEvento)
	{
	case EVENTO_TEMPESTADE:

		do {

			epicentroX = rand() % this->dimX + 1;
			
			epicentroY = rand() % this->dimY + 1;
		
		} while (epicentroX >= 0 + 2 && epicentroX < this->dimX - 3 && epicentroX >= 0 + 2 && epicentroY <= this->dimY - 3);

		TrataEventoTempestade(epicentroX, epicentroY);

		// executa codigo para a tempestade
		break;
	case EVENTO_SEREIAS:
		
		indice = rand() % navios.size() + 1;

		TrataEventoSereias(indice);

		break;

	default:
		if (Evento->ValidaEventoCalmaria() == true)
			Evento->TrataEvento();
		else
			Evento->TrataEvento();
		break;
	}
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

	this->EstadoEvento = EVENTO_ON;

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
