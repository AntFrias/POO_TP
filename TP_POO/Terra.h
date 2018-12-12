#ifndef TERRA_H
#define TERRA_H

#include "Superficie.h"

class Terra : public Superficie {

	char tipo;

public:
	Terra(int x, int y, char auxtipo = '+') : tipo(auxtipo), Superficie(x, y) {};
	virtual bool VerificaCelulaMar()const;
	bool VerificaCelulaTerra() const;
	virtual char getTipo()const;
	~Terra();
};

#endif // !TERRA_H