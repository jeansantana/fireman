#ifndef CELL_H
#define CELL_H

#include "door.h"
#include "utils.h"
#include "point.h"

class cell {
	tile_type tile;
	door * d;
	point * position;

public:
	cell() {

	}
	cell(tile_type tile, door * d, point * position) {
		this->tile = tile;
		this->d = d;
		this->position = position;
	}

	door* getDoor() {
		return d;
	}

	void setDoor(door* d) {
		this->d = d;
	}

	point* getPosition() {
		return position;
	}

	void setPosition(point* position) {
		this->position = position;
	}

	tile_type getTile() {
		return tile;
	}

	void setTile(tile_type tile) {
		this->tile = tile;
	}
};

#endif // CELL_H
