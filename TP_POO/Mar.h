#ifndef MAR_H
#define MAR_H
using namespace std;
class Mar {

	char t;
	int x, y;



public:
	Mar(int x,int y, char t='.');

	const int getX()const ;

	const int getY() const;

	const char getChar() const;

	Mar & getMar();

	~Mar();
};
#endif //MAR_H
