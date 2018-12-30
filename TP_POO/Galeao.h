#ifndef GALEAO_H
#define GALEAO_H

#include "Navios.h"

class Galeao : public Navios
{
	int QuantMercadoria;
	int QuantPeixe;

public:
	Galeao(Mundo *mundo, int coordx, int coordy, int estado) : QuantMercadoria(0), QuantPeixe(0), Navios(mundo, 'G',coordx, coordy, 40, 400, estado){};

	virtual Navios * Duplica()const;

	virtual void AbasteceAguaNavio();
	void soldadosBebemAgua();
	virtual string moveNavioAuto(int turnoAtual);
	virtual void retiraAgua(int agua);
	virtual void retiraSoldados(int soldados);
	virtual int getMaxSoldados();
	virtual void daMetade(int x, int y);
	void serConquistadoaDeriva();
	int getMaxAgua();
	int getAgua();
	virtual void adicionaAgua(int agua);
	virtual int moveNavio(int direcao, int turnoJogo = 0)override;

	virtual int getMercadoriaNavio()const { return this->QuantMercadoria; }
	virtual void setMercadoriaNavio(int Quant); // este metodo mete a quantidade total de mercadoria  =  Quant}
	virtual void adicionaMercadoriaNavio(int quantCarga);
	virtual void RetiraMercadoriaNavio(int quantCarga);
	virtual int VerificaMaxMercadoria()const { return GALEAO_QUANT_MAX_CARGA; }

	virtual int getQuantidadePeixe()const;
	virtual void setQuantidadePeixe(int quantpeixe);
	virtual void AdicionaQuantidadePeixe(int quantpeixe);

	virtual void setPonteiroSaveMundo(Mundo *mundo);

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
	string acao(int xaAtacar, int yaAtacar);
	virtual string combate(int quemVouAtacar);
	~Galeao();
};
#endif // !GALEAO_H
