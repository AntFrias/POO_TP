#ifndef ESCUNA_H
#define ESCUNA_H

#include "Navios.h"

class Escuna : public Navios
{
	int QuantMercadoria;
	int QuantPeixe;

public:
	Escuna(Mundo *mundo, int coordx, int coordy, int estado) : QuantMercadoria(0), QuantPeixe(0), Navios(mundo,'E',coordx, coordy, 10, 100, estado) {};
	virtual void AbasteceAguaNavio();
	virtual int moveNavio(int direcao)override;
	virtual void setCargaNavio(int quantCarga)override;
	virtual void RetiraCargaNavio(int quantCarga);
	virtual void retiraAgua(int agua);
	virtual int getMaxSoldados();
	virtual void retiraSoldados(int soldados);
	string TrataNavioTempestade();
	int FmoveEsquerda();
	int FmoveDireita();
	int FmoveCima();
	int FmoveBaixo();
	int FmoveCimaEsquerda();
	int FmoveCimaDireita();
	int FmoveBaixoEsquerda();
	int FmoveBaixoDireita();
	virtual const int sou()const override;
	int getMaxAgua();
	int getAgua();
	virtual void adicionaAgua(int agua);
	virtual void daMetade(int x, int y);
	void serConquistadoaDeriva();
	virtual string moveNavioAuto();
	void soldadosBebemAgua();
	bool VerificaCargaNavio(int novaCarga);
	virtual string combate(int quemVouAtacar);
	~Escuna();
};

#endif // !ESCUNA_H