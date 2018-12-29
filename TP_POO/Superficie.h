#ifndef SUPERFICIE_H
#define SUPERFICIE_H

#define TEMPO_REGENERACAO_PEIXE 10

using namespace std;

class Superficie
{
protected:
	int x, y;

public:
	Superficie(int coordx, int coordy) : x(coordx), y(coordy) {};
	virtual bool VerificaCelulaMar()const = 0;
	virtual bool VerificaCelulaTerra()const = 0;
	int getX()const;
	int getY()const;
	virtual int getTurno()const = 0;
	virtual void PescaCardumeMar(int turnoPescaria) = 0;
	virtual void VerificaRegenacaoPeixe(int TurnoAtual) = 0;
	virtual bool VerificaCardumePeixe()const = 0;
	virtual bool VerificaCelulaPeixe()const = 0;


	virtual ~Superficie();
	
};

#endif // !SUPERFICIE_H


