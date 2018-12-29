#ifndef PORTO_H
#define PORTO_H

#include "Navios.h"

using namespace std;



class Porto {

	char TipoPorto;
	int x, y;
	int numSoldados;
	int Mercadoria;
	int bancoJogador;

public:
	Porto(int x, int y, char tipoPorto, int nSoldados, int tMercadoria, int bancojogador = 0);
	bool verificaPortoAmigo();
	void setMercadoria(int tMercadoria);
	int getMercadoria()const;
	void setNumSoldados(int nSoldados);
	int getNumSoldados()const;

	void setBancoJogador(int valor);
	void adicionaBancoJogador(int valor);
	int getBancoJogador()const;


	const int getX() const;
	const int getY() const;
	void setX(int x);
	void setY(int y);
	void MudaTipoPorto(char letra);
	const char getChar() const;
	Porto & getPorto();
	string getInfoPorto();
	~Porto();
};


#endif //PORTO_H 




