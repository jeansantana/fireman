#ifndef POINT_H
#define POINT_H

#include "utils.h"
#include <cstddef>

class point {

	int x;
	int y;

public:
	point() {

	}

	point(int x, int y) {
		this->x = x;
		this->y = y;
	}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	void setX(int x) {
		this->x = x;
	}

	void setY(int y) {
		this->y = y;
	}

	direction getDirection(point * target) {
		direction res = LEFT;
		if (target->getX() == this->x && target->getY() == this->y - 1) {
			res = LEFT;
		} else if (target->getX() == this->x + 1 && target->getY() == this->y) {
			res = DOWN;
		} else if (target->getX() == this->x && target->getY() == this->y + 1) {
			res = RIGHT;
		} else if (target->getX() == this->x - 1 && target->getY() == this->y) {
			res = UP;
		}
		return res;
	}

	point * getPointByDirection(direction d) {
		point * p = NULL;
		if (d == LEFT) {
			p = new point(x, y - 1);
		} else if (d == DOWN) {
			p = new point(x + 1, y);
		} else if (d == RIGHT){
			p = new point(x, y + 1);
		} else if (d == UP) {
			p = new point(x - 1, y);
		}
		return p;
	}

	point * getDoorUL() {
		return new point(x, y);
	}

	point * getDoorUR() {
		return new point(x, y + 1);
	}

	point * getDoorDL() {
		return new point(x + 1, y);
	}

	point * getDoorDR() {
		return new point(x + 1, y + 1);
	}
};

#endif //POINT_H
