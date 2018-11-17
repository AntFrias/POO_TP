#ifndef MUNDO_H
#define MUNDO_H
#include "Mar.h"
#include "Terra.h"
#include "Porto.h"
#include <vector>

class Mundo {

	vector <Mar *> mar; 
	vector <Terra *> terra;
	vector <Porto *> porto;


public:
	Mundo();
	void criaCelulaMar(int x,int y);

	void criaCelulaTerra(int x, int y);

	void criaCelulaPorto(int x, int y,char t);

	const vector < const Mar *> getVetorMar() const ;


	~Mundo();
};


#endif //MUNDO_H
