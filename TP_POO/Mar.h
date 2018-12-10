#ifndef MAR_H
#define MAR_H

#include "Superficie.h"

class Mar : public Superficie {

	char tipo;
	int TurnoPesca;
	bool CardumePeixe;

public:

	Mar(int x, int y, char auxtipo = '.') : tipo(auxtipo), CardumePeixe(false),TurnoPesca(0), Superficie(x, y) {}
	virtual char getTipo()const;
	void PescaCardumeMar(int turnoPescaria);
	void VerificaRegenacaoPeixe(int TurnoAtual);
	bool VerificaCardumePeixe();
	~Mar();
};

#endif // !MAR_H