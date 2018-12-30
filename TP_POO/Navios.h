#ifndef NAVIOS_H
#define NAVIOS_H
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>

#define CELULA_MAR 1 
#define CELULA_TERRA 2 
#define CELULA_PORTO_AMIGO 3
#define CELULA_PORTO_INIMIGO 4
#define CELULA_NAVIO 5
#define CELULA_SEM_PORTO 6
#define CELULA_NAVIO_PIRATA 7
#define CELULA_NAVIO_NORMAL 8

#define MOVE_INVALIDO 0
#define MOVE_VALIDO 1

#define DESLOCAMENTO_NAVIO_BASE 0
#define DESLOCAMENTO_NAVIO_RAPIDO 1

#define VELEIRO_QUANT_MAX_CARGA 40
#define GALEAO_QUANT_MAX_CARGA 70
#define ESCUNA_QUANT_MAX_CARGA 20
#define FRAGATA_QUANT_MAX_CARGA 0
#define TARTARUGA_QUANT_MAX_CARGA 0

#define VELEIRO_MAX_AGUA 200
#define GALEAO_MAX_AGUA 400
#define ESCUNA_MAX_AGUA 100
#define FRAGATA_MAX_AGUA 500
#define TARTARUGA_MAX__AGUA 1000 

#define VELEIRO_MAX_SOLDADOS 20
#define GALEAO_MAX_SOLDADOS 40
#define ESCUNA_MAX_SOLDADOS 10
#define FRAGATA_MAX_SOLDADOS 50
#define TARTARUGA_MAX_SOLDADOS 80

enum movimentosNavios {

	naoMove = 0,
	moveCima,
	moveBaixo,
	moveEsquerda,
	moveDireita,
	moveCimaEsquerda,
	moveCimaDireita,
	moveBaixoEsquerda,
	moveBaixoDireita

};
enum estadoNavio {

	normal = 0,
	pirata,
	autoMove,
	atracado,
	afundado,
	aDeriva,
	calmaria,
	motim,
	vaiPara

};
using namespace std;

class Mundo;

class Navios
{
private:
	
	static int IncNavio;
	int id;
	char tipo;
	
protected:
	Mundo *mundo;
	int estado;
	int x, y, xVaiPara, yVaiPara;
	int quantSoldados;
	int quantAgua;
	bool zonaEvento;


public:
	Navios();
	Navios(Mundo *mundo, char tipo, int x, int y, int quantSoldados, int quantAgua = 0, int estado=normal);
	
	virtual Navios * Duplica()const = 0;
	
	virtual int moveNavio(int direcao, int turnoJogo = 0)=0;
	virtual string combate(int quemVouAtacar) = 0;
	virtual int getMaxAgua() = 0;
	virtual void serConquistadoaDeriva() = 0;
	virtual int getMaxSoldados()=0;
	virtual void daMetade(int x,int y) = 0;
	virtual int getAgua() = 0;
	virtual void retiraAgua(int agua)=0;
	virtual void retiraSoldados(int soldados)=0;
	virtual void adicionaAgua(int agua) = 0;
	virtual void soldadosBebemAgua() = 0;

	virtual int getMercadoriaNavio()const = 0;
	virtual void setMercadoriaNavio(int Quant) = 0;
	virtual void adicionaMercadoriaNavio(int quantCarga) = 0;
	virtual void RetiraMercadoriaNavio(int quantCarga) = 0;
	virtual int VerificaMaxMercadoria()const = 0;

	virtual int getQuantidadePeixe()const = 0;
	virtual void setQuantidadePeixe(int quantpeixe) = 0;
	virtual void AdicionaQuantidadePeixe(int quantpeixe) = 0;

	virtual void setPonteiroSaveMundo(Mundo *mundo) = 0;


	virtual string TrataNavioTempestade() = 0;
	virtual const int sou() const =0;
	virtual string moveNavioAuto(int turnoAtual)=0;
	int randNumber(int nSoldados);
	int getNumSoldados();
	void setNumSoldados(int num);

	int getEstado()const;
	void setEstado(int estado);

	char getTipo()const;
	int getX()const;
	int getY()const;
	void setX(int x);
	void setY(int y);
	int getXvaiPara()const;
	int getYvaiPara()const;
	void setXvaiPara(int x);
	void setYvaiPara(int y);
	string AlteraSoldadosPosEvento(int prob);
	const int getId()const;
	const Navios * getNavio() const;	
	int getIncNavio();
	virtual void AbasteceAguaNavio() = 0;
	~Navios();


};



#endif //NAVIOS_H

