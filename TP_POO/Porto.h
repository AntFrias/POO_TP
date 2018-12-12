#ifndef PORTO_H
#define PORTO_H

#include "Navios.h"

using namespace std;

class Porto {

	char TipoPorto;
	int x, y;

public:
	Porto(int x, int y, char t);
	bool verificaPortoAmigo();
	const int getX() const;
	const int getY() const;
	const char getChar() const;
	Porto & getPorto();
	~Porto();
};


#endif //PORTO_H 




