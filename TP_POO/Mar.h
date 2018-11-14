#ifndef MAR_H
#define MAR_H
class Mar {

	char t;
	int x, y;



public:
	Mar();
	Mar(int x,int y, char t='.');

	char getTipo();


	~Mar();
};
#endif //MAR_H
