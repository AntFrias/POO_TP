#ifndef MAR_H
#define MAR_H

#include "Superficie.h"

class Mar : public Superficie {

	char tipo;

public:

	Mar(int x, int y, char auxtipo = '.') : tipo(auxtipo), Superficie(x, y) {}
	virtual char getTipo()const;
	~Mar();
};

#endif // !MAR_H