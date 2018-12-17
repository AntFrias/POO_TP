#ifndef FRAGATA_H
#define FRAGATA_H

#include "Navios.h"

class Fragata : public Navios
{

public:
	Fragata(Mundo *mundo, int coordx, int coordy) : Navios(mundo, 'F', coordx, coordy, 50, 500) {};
	virtual void AbasteceAguaNavio();
	virtual int moveNavio(int direcao);
	virtual void combate();
	void acao(int xaAtacar, int yaAtacar);
	int FmoveEsquerda();
	int FmoveDireita();
	int FmoveCima();
	int FmoveBaixo();
	int FmoveCimaEsquerda();
	int FmoveCimaDireita();
	int FmoveBaixoEsquerda();
	int FmoveBaixoDireita();
	bool souFragata();
	int getMaxAgua();
	~Fragata();
};

#endif // !FRAGATA_H
