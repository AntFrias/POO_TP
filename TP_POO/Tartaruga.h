#ifndef TARTARUGA_H
#define TARTARUGA_H

#include "Navios.h"

class Tartaruga : public Navios
{

public:
	Tartaruga(Mundo *mundo, int coordx, int coordy, int estado) : Navios(mundo, 'T', coordx, coordy, 80, 1000, estado) {};

	virtual Navios * Duplica()const;

	virtual void AbasteceAguaNavio();
	void soldadosBebemAgua();
	virtual void retiraAgua(int agua);
	virtual void retiraSoldados(int soldados);
	virtual void daMetade(int x, int y);
	virtual void serConquistadoaDeriva();
	virtual string moveNavioAuto(int turnoAtual);
	virtual int moveNavio(int direcao, int turnoJogo = 0);
	virtual string combate(int quemVouAtacar);
	void conquistaPorto(int xPorto, int yPorto);
	void conquistaPortoAmigo(int xPorto, int yPorto);
	string acaoPortoAmigo();
	virtual string acaoPorto();


	virtual int getMercadoriaNavio()const;
	virtual void setMercadoriaNavio(int quantCarga);
	virtual void adicionaMercadoriaNavio(int quantCarga);
	virtual void RetiraMercadoriaNavio(int quantCarga);
	virtual int VerificaMaxMercadoria()const;

	virtual int getQuantidadePeixe()const;
	virtual void setQuantidadePeixe(int quantpeixe);
	virtual void AdicionaQuantidadePeixe(int quantpeixe);
	
	string TrataNavioTempestade();
	int FmoveEsquerda(int move);
	int FmoveDireita(int move);
	int FmoveCima(int move);
	int FmoveBaixo(int move);
	int FmoveCimaEsquerda(int move);
	int FmoveCimaDireita(int move);
	int FmoveBaixoEsquerda(int move);
	int FmoveBaixoDireita(int move);
	virtual const int sou()const override;
	int getMaxAgua();
	virtual int getMaxSoldados();
	int getAgua();
	virtual void adicionaAgua(int agua);
	string acao(int xaAtacar, int yaAtacar);
	~Tartaruga();
};

#endif // TARTARUGA_H

