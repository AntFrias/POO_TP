#ifndef GALEAO_H
#define GALEAO_H

#include "Navios.h"

class Galeao : public Navios
{
	int QuantMercadoria;
	int QuantPeixe;

public:
	Galeao(Mundo *mundo, int coordx, int coordy, int estado) : QuantMercadoria(0), QuantPeixe(0), Navios(mundo, 'G',coordx, coordy, 40, 400, estado){};
	virtual void AbasteceAguaNavio();
	void soldadosBebemAgua();
	virtual string moveNavioAuto();
	int getMaxAgua();
	int getAgua();
	void adicionaAgua(int agua);
	virtual int moveNavio(int direcao)override;
	virtual void setCargaNavio(int quantCarga);
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
	bool VerificaCargaNavio(int novaCarga);
	int sou();
	virtual string combate(int quemVouAtacar);
	~Galeao();
};
#endif // !GALEAO_H
