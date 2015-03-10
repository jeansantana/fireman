#include <iostream>
#include <cstdio>
#include "../classes/point.h"
#include "../classes/door.h"
#include "../classes/cell.h"
#include "../classes/exploitElement.h"
#include <vector>

using namespace std;

void printPoint(point * p) {
	cout << "(" << p->getX() << ", " << p->getY() << ") ";
}

void printDoors(vector<vector<door> > doors) {
	int tam = doors.size();
	cout << "TM: " << tam << endl;
	for (int i = 0; i < tam; ++i) {
		for (int j = 0; j < tam; ++j) {
			cout << "[" << doors[i][j].getState() << "/" << doors[i][j].getNextState() << "] ";
		}
		cout << endl;
	}
}


void printVectorInt(vector<vector<int> > board) {
	int tam = board.size();
	for (int i = 0; i < tam; ++i) {
		for (int j = 0; j < tam; ++j) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

void printVectorCellBoard(vector<vector<cell> > board) {
	int tam = board.size();
	for (int i = 0; i < tam; ++i) {
		for (int j = 0; j < tam; ++j) {
			cout << board[i][j].getTile() << " ";
		}
		cout << endl;
	}
}

/**
 * verifica a 4-adjacencia de p, e retorna apenas os pontos dentro do tabuleiro (board)
 *
 * */

vector<cell> getAdjacentes(vector<vector<cell> > board, point * p) {
	//TODO
	int maxBound = board.size() - 1;
	vector<cell> adjs;

	if (p->getY() - 1 >= 0) {
		adjs.push_back(board[p->getX()][p->getY() - 1]);
	}

	if (p->getX() + 1 <= maxBound) {
		adjs.push_back(board[p->getX() + 1][p->getY()]);
	}

	if (p->getY() + 1 <= maxBound) {
		adjs.push_back(board[p->getX()][p->getY() + 1]);
	}

	if (p->getX() - 1 >= 0) {
		adjs.push_back(board[p->getX() - 1][p->getY()]);
	}

	return adjs;
}
/**
 * retorna true se for possível ir de a para b, false caso contrário.
 *
 * */


void findPath(vector<vector<cell> > board, point * s,
		vector<vector<int> > * Mexp) {
	vector<cell> lAdja = getAdjacentes(board, s);
	int tam_lAdja = lAdja.size();

	for (int i = 0; i < tam_lAdja; ++i) {
		point *v = new point(lAdja[i].getPosition()->getX(),
				lAdja[i].getPosition()->getY());
		/*if ((*Mexp)[v->getX()][v->getY()] == 0 && pathExists(board, s, v)) {
			(*Mexp)[v->getX()][v->getY()] = 1;
			findPath(board, v, Mexp);
		}*/
	}

}

void printElementExploit(exploitElement e) {
	cout << "[U: " << e.isUp() <<
			", D: " << e.isDown() <<
			", L: " << e.isLeft() <<
			", R: " << e.isRight() << "]; ";
}

bool avalCanMove(vector<vector<door> > doors, point * pDoorFrom, point * pDoorTo, int typeDoorFrom, int typeDoorTo, int typeNextDoor) {
	return (doors[pDoorFrom->getX()][pDoorFrom->getY()].getState() == typeDoorFrom
			&& doors[pDoorFrom->getX()][pDoorFrom->getY()].getNextState() == typeNextDoor)
			||
			(doors[pDoorTo->getX()][pDoorTo->getY()].getState() == typeDoorTo &&
			doors[pDoorTo->getX()][pDoorTo->getY()].getNextState() == typeNextDoor);
}

bool canMove(vector<vector<door> > doors, point *s, point *f) {
	bool canMove = false;
	if (s->getDirection(f) == UP) {
		canMove = avalCanMove(doors, s->getDoorUR(), s->getDoorUL(), 4, 1, 2);
	} else if (s->getDirection(f) == DOWN) {
		canMove = avalCanMove(doors, s->getDoorDL(), s->getDoorDR(), 1, 4, 3);
	} else if (s->getDirection(f) == RIGHT) {
		canMove = avalCanMove(doors, s->getDoorUR(), s->getDoorDR(), 3, 2, 1);
	} else if (s->getDirection(f) == LEFT) {
		canMove = avalCanMove(doors, s->getDoorUL(), s->getDoorDL(), 3, 2, 4);
	}
	return canMove;
}

int main() {
	int n;
	int a, b, c, d;
	while (scanf("%d", &n) == 1) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		point s(a, b);
		point f(c, d);


		vector< vector<cell> > board;
		vector< vector <door> > doors;

		//vector<vector<int> > Mexp;

		//leitura da matriz de walls

		/*for (int i = 0; i < n; ++i) {
			vector<int> line;
			line.assign(n, 0);
			//Mexp.assign(n, line);
		}*/

		for (int i = 0; i < n; i++) {
			vector<cell> line;
			for (int j = 0; j < n; j++) {
				int wall;
				cin >> wall;
				cell c;
				point * p = new point(i, j);
				c.setPosition(p);
				tile_type tt = wall == 1 ? WALL : GROUND;
				c.setTile(tt);
				line.push_back(c);
			}
			board.push_back(line);
		}

		//reading doors current state matrix
		for (int i = 0; i < n + 1; ++i) {
			vector<door> line;
			for (int j = 0; j < n + 1; ++j) {
				int cDoor;
				cin >> cDoor;
				point * p = new point(i, j);
				//door (currenteState, nextState, point)
				door d (cDoor, -1, p);
				line.push_back(d);
			}
			doors.push_back(line);
		}
		//reading doors next state matrix
		for (int i = 0; i < n + 1; ++i) {
			for (int j = 0; j < n + 1; ++j) {
				int nDoor;
				cin >> nDoor;
				doors[i][j].setNextState(nDoor);
			}
		}

		cout << canMove(doors, new point(0, 0), new point(0, 1)) << endl;
		cout << canMove(doors, new point(2, 1), new point(2, 2)) << endl;

		/*cout << "=======BEGIN-INSTANCE=======\nBOARD\n";
		printVectorCellBoard(board);
		cout << "DOORS\n";
		printDoors(doors);
		cout << "=======END-INSTANCE=======\n";*/

	}

	return 0;
}


