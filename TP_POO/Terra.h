#ifndef TERRA_H
#define TERRA_H

#include "Superficie.h"

class Terra : public Superficie {

	char tipo;

public:
	Terra(int x, int y, char auxtipo = '+') : tipo(auxtipo), Superficie(x, y) {};
	virtual bool VerificaCelulaMar()const;
	bool VerificaCelulaTerra()const;
	virtual char getTipo()const;
	virtual int getTurno()const { return -2; };
	virtual void PescaCardumeMar(int turnoPescaria);
	virtual void VerificaRegenacaoPeixe(int TurnoAtual);
	virtual bool VerificaCardumePeixe()const;
	virtual bool VerificaCelulaPeixe()const { return false; };
	~Terra();
};

#endif // !TERRA_H