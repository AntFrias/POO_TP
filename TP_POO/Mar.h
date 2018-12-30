#ifndef MAR_H
#define MAR_H

#include "Superficie.h"

using namespace std;

class Mar : public Superficie {

	char tipo;

	int TurnoPesca;
	bool CardumePeixe;
	bool celulaPeixe;

public:
	Mar();
	Mar(const Mar & aux);
	Mar(int x, int y, char auxtipo, bool peixe, int turnoDefault, bool celulapeixe = false ) : tipo(auxtipo), CardumePeixe(peixe),TurnoPesca(turnoDefault), celulaPeixe(celulapeixe), Superficie(x, y) {}
	virtual Mar * Duplica()const;
	virtual char getTipo()const;
	virtual int getTurno()const { return this->TurnoPesca; };
	virtual bool VerificaCelulaMar()const;
	bool VerificaCelulaTerra() const;
	virtual void PescaCardumeMar(int turnoPescaria);
	virtual void VerificaRegenacaoPeixe(int TurnoAtual);
	virtual bool VerificaCardumePeixe()const;
	virtual bool VerificaCelulaPeixe()const;
	~Mar();
};

#endif // !MAR_H