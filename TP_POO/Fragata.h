#ifndef FRAGATA_H
#define FRAGATA_H

#include "Navios.h"

class Fragata : public Navios
{

public:
	Fragata(Mundo *mundo, int coordx, int coordy, int estado) : Navios(mundo, 'F', coordx, coordy, 50, 500, estado) {};
	virtual void AbasteceAguaNavio();
	void soldadosBebemAgua();
	virtual void retiraAgua(int agua);
	virtual void retiraSoldados(int soldados);
	virtual void daMetade(int x,int y);
	virtual void serConquistadoaDeriva();
	virtual string moveNavioAuto();
	virtual int moveNavio(int direcao);
	virtual string combate(int quemVouAtacar);
	string acao(int xaAtacar, int yaAtacar);
	void conquistaPorto(int xPorto,int yPorto);
	virtual string acaoPorto();
	virtual void setCargaNavio(int quantCarga)override;
	virtual void RetiraCargaNavio(int quantCarga);
	string TrataNavioTempestade();
	int FmoveEsquerda();
	int FmoveDireita();
	int FmoveCima();
	int FmoveBaixo();
	int FmoveCimaEsquerda();
	int FmoveCimaDireita();
	int FmoveBaixoEsquerda();
	int FmoveBaixoDireita();
	int sou();
	int getMaxAgua();
	virtual int getMaxSoldados();
	int getAgua();
	virtual void adicionaAgua(int agua);
	~Fragata();
};

#endif // !FRAGATA_H
