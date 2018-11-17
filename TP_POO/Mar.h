#ifndef MAR_H
#define MAR_H
class Mar {

	char t;
	int x, y;



public:
	Mar();
	Mar(int x,int y, char t='.');

	int getX();

	int getY();

	Mar & getMar();

	~Mar();
};
#endif //MAR_H
