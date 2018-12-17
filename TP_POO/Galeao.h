#ifndef GALEAO_H
#define GALEAO_H

#include "Navios.h"

class Galeao : public Navios
{
	int QuantMercadoria;
	int QuantPeixe;

public:
	Galeao(Mundo *mundo, int coordx, int coordy) : QuantMercadoria(0), QuantPeixe(0), Navios(mundo, 'G', coordx, coordy, 40, 400){};
	virtual void AbasteceAguaNavio();
	int getMaxAgua();
	virtual int moveNavio(int direcao)override;
	int FmoveEsquerda();
	int FmoveDireita();
	int FmoveCima();
	int FmoveBaixo();
	int FmoveCimaEsquerda();
	int FmoveCimaDireita();
	int FmoveBaixoEsquerda();
	int FmoveBaixoDireita();
	bool VerificaCargaNavio(int novaCarga);
	bool souGaleao();
	void acao(int xaAtacar, int yaAtacar);
	virtual void combate();
	~Galeao();
};
#endif // !GALEAO_H
