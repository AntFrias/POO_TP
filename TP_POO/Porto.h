#ifndef PORTO_H
#define PORTO_H
using namespace std;
class Porto {

	char t;
	int x, y;


public:
	Porto(int x, int y, char t);
	const int getX() const;
	const int getY() const;
	const char getChar() const;
	Porto & getPorto();
	~Porto();
};


#endif //PORTO_H 




