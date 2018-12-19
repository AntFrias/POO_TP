#ifndef FRAGATA_H
#define FRAGATA_H

#include "Navios.h"

class Fragata : public Navios
{

public:
	Fragata(Mundo *mundo, bool pirata, int coordx, int coordy) : Navios(mundo, 'F',pirata, coordx, coordy, 50, 500) {};
	virtual void AbasteceAguaNavio();
	void soldadosBebemAgua();
	void moveNavioAuto();
	virtual int moveNavio(int direcao);
	virtual string combate();
	string acao(int xaAtacar, int yaAtacar);
	void conquistaPorto(int xPorto,int yPorto);
	bool souPirata()const;
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
	int getAgua();
	void adicionaAgua(int agua);
	~Fragata();
};

#endif // !FRAGATA_H
