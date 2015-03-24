#ifndef DOOR_H
#define DOOR_H

#include "point.h"

class door {
	int id;
	int currentState;
	int nextState;
	point * position;
public:
	door() {

	}

	door(int id, int currentState, int nextState, point * position) {
		this->currentState = currentState;
		this->nextState = nextState;
		this->position = position;
		this->id = id;
	}

	int getId() {
		return id;
	}

	void setId(int id) {
		this->id = id;
	}

	int getState() {
		return currentState;
	}

	void setCurrentState(int newState) {
		this->currentState = newState;
	}

	void setNextState(int newState) {
		this->nextState = newState;
	}

	int getNextState() {
		return nextState;
	}

	void moveDoor() {
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
