#ifndef FRAGATA_H
#define FRAGATA_H

#include "Navios.h"

class Fragata : public Navios
{

public:
	Fragata(Mundo *mundo, int coordx, int coordy) : Navios(mundo, 'F', coordx, coordy, 50, 500) {};
	virtual void AbasteceAguaNavio();
	void soldadosBebemAgua();
	void moveNavioAuto();
	virtual int moveNavio(int direcao);
	virtual string combate();
	string acao(int xaAtacar, int yaAtacar);
	virtual void setCargaNavio(int quantCarga)override;
	virtual void RetiraCargaNavio(int quantCarga);
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
