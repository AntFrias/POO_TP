#ifndef VELEIRO_H
#define VELEIRO_H

#include "Navios.h"


class Veleiro : public Navios
{
	int QuantMercadoria;
	int QuantPeixe;

public:
	Veleiro(Mundo *auxMundo, int coordx, int coordy) : QuantMercadoria(0), QuantPeixe(0), Navios(auxMundo,'V', coordx,coordy, 20, 200){};
	virtual void AbasteceAguaNavio();
	void soldadosBebemAgua();
	int getMaxAgua();
	int getAgua();
	void adicionaAgua(int agua);
	virtual int moveNavio(int direcao);
	virtual void combate();
	int FmoveEsquerda();
	int FmoveDireita();
	int FmoveCima();
	int FmoveBaixo();
	int FmoveCimaEsquerda();
	int FmoveCimaDireita();
	int FmoveBaixoEsquerda();
	int FmoveBaixoDireita();
	bool souVeleiro();
	void acao(int xaAtacar, int yaAtacar);
	bool VerificaCargaNavio(int novaCarga);
	~Veleiro();
};
#endif // !VELEIRO_H
