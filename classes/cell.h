#ifndef CELL_H
#define CELL_H

#include "door.h"
#include "point.h"

class cell {
	tile_type tile;
	point * position;

public:
	cell() {

	}

	cell(tile_type tile, point * position) {
		this->tile = tile;
		this->position = position;
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
