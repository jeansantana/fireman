#ifndef DOOR_H
#define DOOR_H

#include "point.h"

class door {
	int currentState;
	int nextState;
	point * position;
public:
	door() {

	}

	door(int currentState, int nextState, point * position) {
		this->currentState = currentState;
		this->nextState = nextState;
		this->position = position;
	}

	int getState() {
		return currentState;
	}

	int getNextState() {
		return nextState;
	}

	/**
	 * Return the next tile to go to.
	 * */
	point * moveDoor() {
		int aux = currentState;
		currentState = nextState;
		nextState = aux;
	}

	point * getPosition() {
		return position;
	}

	void setPosition(point * position) {
		this->position = position;
	}
};

#endif // DOOR_H
