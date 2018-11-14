#ifndef TERRA_H
#define TERRA_H
class Terra {

	char t;
	int x, y;

public:
	Terra(int x, int y, char t);
	char getT();
	int getX();
	int getY();
	~Terra();
};

#endif //TERRA_H