#ifndef ESCUNA_H
#define ESCUNA_H

#include "Navios.h"

#define PEIXE_PESCADO 1 

class Escuna : public Navios
{
	int QuantMercadoria;
	int QuantPeixe;

public:
	Escuna(Mundo *mundo, int coordx, int coordy, int estado) : QuantMercadoria(0), QuantPeixe(0), Navios(mundo,'E',coordx, coordy, 10, 100, estado) {};
	
	virtual Navios * Duplica()const;
	
	virtual void AbasteceAguaNavio();

	virtual int moveNavio(int direcao, int turnoJogo = 0)override;


	virtual int getMercadoriaNavio()const { return this->QuantMercadoria; }
	virtual void setMercadoriaNavio(int Quant); // este metodo mete a quantidade total de mercadoria  =  Quant}
	virtual void adicionaMercadoriaNavio(int quantCarga);
	virtual void RetiraMercadoriaNavio(int quantCarga);
	virtual int VerificaMaxMercadoria()const { return ESCUNA_QUANT_MAX_CARGA; }
	virtual int getQuantidadePeixe()const { return this->QuantPeixe; };
	virtual void setQuantidadePeixe(int quantpeixe);
	virtual void AdicionaQuantidadePeixe(int quantpeixe);


	virtual void retiraAgua(int agua);
	virtual int getMaxSoldados();
	virtual void retiraSoldados(int soldados);
	string TrataNavioTempestade();
	int FmoveEsquerda(int turnoJogo);
	int FmoveDireita(int turnoJogo);
	int FmoveCima(int turnoJogo);
	int FmoveBaixo(int turnoJogo);
	int FmoveCimaEsquerda(int turnoJogo);
	int FmoveCimaDireita(int turnoJogo);
	int FmoveBaixoEsquerda(int turnoJogo);
	int FmoveBaixoDireita(int turnoJogo);
	virtual const int sou()const override;
	int getMaxAgua();
	int getAgua();
	virtual void adicionaAgua(int agua);
	virtual void daMetade(int x, int y);
	void serConquistadoaDeriva();
	virtual string moveNavioAuto(int turnoAtual);
	void soldadosBebemAgua();
	virtual string combate(int quemVouAtacar);
	~Escuna();
};

#endif // !ESCUNA_H