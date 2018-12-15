#ifndef EVENTOS_H
#define EVENTOS_H

#define TTL_TEMPESTADE 1
#define TTL_SEREIA 1
#define TTL_CALMARIA 3
#define TTL_MOTIM 4

class Mundo;

class Eventos
{
	Mundo *mundo;

	int TTL;
	

public:

	Eventos(Mundo *mundo, int TTL);
	virtual bool ValidaEventoCalmaria() = 0;
	virtual void TrataEventoCalmaria() = 0;
	virtual void TrataEventoMotim() = 0;
	~Eventos();
};
#endif // !EVENTOS_H
