#ifndef VELEIRO_H
#define VELEIRO_H

#include "Navios.h"


class Veleiro : public Navios
{
	int QuantMercadoria;
	int QuantPeixe;

public:
	Veleiro(Mundo *auxMundo,int coordx, int coordy,int estado) : QuantMercadoria(0), QuantPeixe(0), Navios(auxMundo,'V',coordx,coordy, 20, 200, estado){};
	virtual void AbasteceAguaNavio();
	virtual string moveNavioAuto();
	void soldadosBebemAgua();
	virtual void retiraSoldados(int soldados);
	virtual int getMaxSoldados();
	virtual void retiraAgua(int agua);
	int getMaxAgua();
	int getAgua();
	virtual void adicionaAgua(int agua);
	virtual int moveNavio(int direcao);
	virtual string combate(int quemVouAtacar);
	virtual void setCargaNavio(int quantCarga)override;
	virtual void RetiraCargaNavio(int quantCarga);
	string TrataNavioTempestade();
	int FmoveEsquerda(int move);
	int FmoveDireita(int move);
	int FmoveCima(int move);
	int FmoveBaixo(int move);
	int FmoveCimaEsquerda(int move);
	int FmoveCimaDireita(int move);
	int FmoveBaixoEsquerda(int move);
	int FmoveBaixoDireita(int move);
	void serConquistadoaDeriva();
	void daMetade(int x, int y);
	virtual const int sou()const override;
	void conquistaPorto(int xPorto, int yPorto);
	string acaoPorto();
	string acao(int xaAtacar, int yaAtacar);
	string acaoRoubo(int xEscuna, int yEscuna);
	bool VerificaCargaNavio(int novaCarga);
	~Veleiro();
};
#endif // !VELEIRO_H
