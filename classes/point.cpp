#include "point.h"

point::point() {

}

point::point(int x, int y) {
	this->x = x;
	this->y = y;
}

int point::getX() {
	return x;
}

int point::getY() {
	return y;
}

void point::setX(int x) {
	this->x = x;
}

void point::setY(int y) {
	this->y = y;
}
