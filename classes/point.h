#ifndef POINT_H
#define POINT_H

class point {

	int x;
	int y;

public:
	point();
	point(int x, int y);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
};

#endif //POINT_H