#ifndef TERRA_H
#define TERRA_H
using namespace std;
class Terra {

	char t;
	int x, y;

public:
	Terra(int x, int y, char t='+');
	const char getChar()const;
	const int getX()const;
	const int getY()const;
	Terra & getTerra();
	~Terra();
};

#endif //TERRA_H