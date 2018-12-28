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
	virtual void retiraAgua(int agua);
	virtual void retiraSoldados(int soldados);
	virtual int getMaxSoldados();
	virtual void daMetade(int x, int y);
	void serConquistadoaDeriva();
	int getMaxAgua();
	int getAgua();
	virtual void adicionaAgua(int agua);
	virtual int moveNavio(int direcao)override;
	virtual void AdicionaMercadoriaNavio(int quantCarga);  
	virtual void setMercadoriaNavio(int Quant); // este metodo mete a quantidade total de mercadoria  =  Quant
	virtual int getMercadoriaNavio()const { return this->QuantMercadoria; }
	virtual void RetiraCargaNavio(int quantCarga);
	bool VerificaCargaNavio(int novaCarga);
	virtual int VerificaMaxCarga() { return GALEAO_QUANT_MAX_CARGA; }
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
	virtual string combate(int quemVouAtacar);
	~Galeao();
};
#endif // !GALEAO_H
