#include "Mundo.h"

using namespace std;
Mundo::Mundo() {

}
void Mundo::criaNavio(char tipo) {




}
void Mundo::criaCelulaMar(int x, int y)
{

	this->mar.push_back(new Mar(x,y));

}
void Mundo::criaCelulaTerra(int x, int y)
{

	this->terra.push_back(new Terra(x, y));

}
void Mundo::criaCelulaPorto(int x, int y,char t)
{

	this->porto.push_back(new Porto(x, y, t));

}

const vector<const Mar*> Mundo::getVetorMar() const
{
	return vector<const Mar *>(this->mar.begin(), this->mar.end());
}

const vector<const Terra*> Mundo::getVetorTerra() const
{
	return vector<const Terra *>(this->terra.begin(), this->terra.end());
}

const vector<const Porto*> Mundo::getVetorPorto() const
{
	return vector<const Porto *>(this->porto.begin(), this->porto.end());
}


Mundo::~Mundo()
{
}
