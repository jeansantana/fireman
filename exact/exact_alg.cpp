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
			cout << "[" << doors[i][j].getState() << "/"
					<< doors[i][j].getNextState() << "] ";
		}
		cout << endl;
	}
}

void printVectorInt(vector<vector<int> > board) {
	int tam = board.size();
	for (int i = 0; i < tam; ++i) {
		for (int j = 0; j < tam; ++j) {
			if (board[i][j] < 10)
				cout << board[i][j] << "  ";
			else
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

	if (p->getY() - 1 >= 0 && board[p->getX()][p->getY() - 1].getTile() == 0) {
		adjs.push_back(board[p->getX()][p->getY() - 1]);
	}

	if (p->getX() + 1 <= maxBound
			&& board[p->getX() + 1][p->getY()].getTile() == 0) {
		adjs.push_back(board[p->getX() + 1][p->getY()]);
	}

	if (p->getY() + 1 <= maxBound
			&& board[p->getX()][p->getY() + 1].getTile() == 0) {
		adjs.push_back(board[p->getX()][p->getY() + 1]);
	}

	if (p->getX() - 1 >= 0 && board[p->getX() - 1][p->getY()].getTile() == 0) {
		adjs.push_back(board[p->getX() - 1][p->getY()]);
	}

	return adjs;
}

void printElementExploit(exploitElement e) {
	cout << "[U: " << e.isUp() << ", D: " << e.isDown() << ", L: " << e.isLeft()
			<< ", R: " << e.isRight() << "]; ";
}

bool avalCanMove(vector<vector<door> > doors, point * pDoorFrom,
		point * pDoorTo, int typeDoorFrom, int typeDoorTo, int typeNextDoor) {
	return (doors[pDoorFrom->getX()][pDoorFrom->getY()].getState()
			== typeDoorFrom
			&& doors[pDoorFrom->getX()][pDoorFrom->getY()].getNextState()
					== typeNextDoor)
			|| (doors[pDoorTo->getX()][pDoorTo->getY()].getState() == typeDoorTo
					&& doors[pDoorTo->getX()][pDoorTo->getY()].getNextState()
							== typeNextDoor);
}

bool canMove(vector<vector<cell> > board, vector<vector<door> > doors, point *s,
		point *f) {
	bool canMove = false;
	if (board[f->getX()][f->getY()].getTile() == GROUND) {
		canMove = true;
	} else if (s->getDirection(f) == UP) {
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

/**
 * retorna true se for possível ir de a para b, false caso contrário.
 *
 * */

void findPath(vector<vector<cell> > board, vector<vector<door> > doors,
		point * s, point *f, vector<vector<int> > * Mexp,
		vector<vector<point> > * paths, int id) {
	if (s->getX() == f->getX() && s->getY() == f->getY())
		return;
	vector<cell> lAdja = getAdjacentes(board, s);
	int tam_lAdja = lAdja.size();
	vector<point> path;
	++id;
	for (int i = 0; i < tam_lAdja; ++i) {
		point *v = new point(lAdja[i].getPosition()->getX(),
				lAdja[i].getPosition()->getY());
		/*printPoint(s);
		 printPoint(v);
		 cout << canMove(board, doors, s, v) << endl;*/
		if ((*Mexp)[v->getX()][v->getY()] == 0 && canMove(board, doors, s, v)) {
			(*Mexp)[v->getX()][v->getY()] = 1;
			findPath(board, doors, v, f, Mexp, paths, id);
		}
	}

}

int dijkstra(vector<vector<cell> > board, vector<vector<door> > doors,
		point * s, int n, int nDoorsComb, int *** Mexp) {
	int (*M1)[n][n][nDoorsComb] = (int (*)[n][n][nDoorsComb]) Mexp;

	return 0;
}

int main() {
	int n, nDoors;
	int a, b, c, d;
	while (scanf("%d", &n) == 1) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		point s(a, b);
		point f(c, d);

		vector<vector<cell> > board;
		vector<vector<door> > doors;
		vector<vector<point> > paths;
		vector<vector<int> > Mexp;

		//leitura da matriz de walls

		for (int i = 0; i < n; ++i) {
			vector<int> line;
			line.assign(n, 0);
			Mexp.assign(n, line);
		}

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

		scanf("%d", &nDoors);
		//reading doors current state matrix

		vector<vector<vector<int> > > MExploit;

		// Set up sizes. (HEIGHT x WIDTH)
		MExploit.resize(n);
		for (int i = 0; i < n; ++i) {
			MExploit[i].resize(n);

			for (int j = 0; j < n; ++j) {
				MExploit[i][j].resize(nDoors);
				MExploit[i][j].assign(n, 0);
			}
		}

		/*for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				for (int k = 0; k < nDoors; k++) {
					cout << MExploit[i][j][k] << " ";
				}
				cout << "\n";
			}
			cout << "\n";
		}*/

		int id = -1;
		for (int i = 0; i < n + 1; ++i) {
			vector<door> line;
			for (int j = 0; j < n + 1; ++j) {
				int cDoor;
				cin >> cDoor;
				point * p = new point(i, j);
				//door (currenteState, nextState, point)
				door d(++id, cDoor, -1, p);
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

		cout << "Pontos inicial e final:\n";
		printPoint(&s);
		printPoint(&f);
		cout << "\n=============BOARD=============\n";
		printVectorCellBoard(board);
		cout << endl << "===============DOORS=============\n" << endl;
		printDoors(doors);
		cout << "============== MOVEMENT MATRIX =============\n";
		findPath(board, doors, &s, &f, &Mexp, &paths, 0);
		printVectorInt(Mexp);
		int ***M;
		dijkstra(board, doors, &s, n, nDoors, M);

		/*cout << canMove(doors, new point(0, 0), new point(0, 1)) << endl;
		 cout << canMove(doors, new point(2, 1), new point(2, 2)) << endl;
		 cout << "Start with your move: \n";
		 int x1, y1, x2, y2;
		 while (scanf("%d %d %d %d", &x1, &y1, &x2, &y2) == 4) {
		 point *p1 = new point(x1, y1);
		 point *p2 = new point(x2, y2);
		 if (canMove(doors, p1, p2)) {
		 cout << "Yes from ";
		 } else {
		 cout << "No from ";
		 }
		 printPoint(p1);
		 cout << "to ";
		 printPoint(p2);
		 cout << endl;
		 }*/

	}

	return 0;
}
