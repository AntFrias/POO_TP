#ifndef ESCUNA_H
#define ESCUNA_H

#include "Navios.h"

class Escuna : public Navios
{
	int QuantMercadoria;
	int QuantPeixe;

public:
	Escuna(Mundo *mundo, int coordx, int coordy) : QuantMercadoria(0), QuantPeixe(0), Navios(mundo, 'E', coordx, coordy, 10, 100) {};
	virtual void AbasteceAguaNavio();
	virtual int moveNavio(int direcao)override;
	int FmoveEsquerda();
	int FmoveDireita();
	int FmoveCima();
	int FmoveBaixo();
	int FmoveCimaEsquerda();
	int FmoveCimaDireita();
	int FmoveBaixoEsquerda();
	int FmoveBaixoDireita();
	int sou();
	int getMaxAgua();
	int getAgua();
	void adicionaAgua(int agua);
	void moveNavioAuto();
	void soldadosBebemAgua();
	bool VerificaCargaNavio(int novaCarga);
	virtual string combate();
	~Escuna();
};

#endif // !ESCUNA_H