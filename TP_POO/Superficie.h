#ifndef SUPERFICIE_H
#define SUPERFICIE_H

#define TEMPO_REGENERACAO_PEIXE 3

class Superficie
{
protected:
	int x, y;

public:
	Superficie(int coordx, int coordy) : x(coordx), y(coordy) {};
	// perguntar este getTipo á prof
	//virtual char getTipo() const = 0;
	virtual bool VerificaCelulaMar()const = 0;
	virtual bool VerificaCelulaTerra()const = 0;
	int getX()const;
	int getY()const;
	virtual ~Superficie();
	
};

#endif // !SUPERFICIE_H


