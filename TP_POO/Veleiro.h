#ifndef VELEIRO_H
#define VELEIRO_H

#include "Navios.h"


class Veleiro : public Navios
{
	int QuantMercadoria;
	int QuantPeixe;

public:
	Veleiro(Mundo *auxMundo, bool Pirata,bool automove, int coordx, int coordy) : QuantMercadoria(0), QuantPeixe(0), Navios(auxMundo,'V', Pirata, coordx,coordy, 20, 200, automove){};
	virtual void AbasteceAguaNavio();
	void moveNavioAuto();
	void soldadosBebemAgua();
	int getMaxAgua();
	int getAgua();
	void adicionaAgua(int agua);
	virtual int moveNavio(int direcao);
	virtual string combate();
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
	void conquistaPorto(int xPorto, int yPorto);
	bool souPirata()const;
	string acaoPorto();
	string acao(int xaAtacar, int yaAtacar);
	bool VerificaCargaNavio(int novaCarga);
	~Veleiro();
};
#endif // !VELEIRO_H
