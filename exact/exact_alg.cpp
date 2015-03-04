#include <iostream>
#include <cstdio>
#include "../classes/point.h"
#include "../classes/door.h"
#include "../classes/cell.h"
#include <vector>

using namespace std;

void printPoint(point * p) {
	cout << "(" << p->getX() << ", " << p->getY() << ") ";
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

void printVectorCell(vector<vector<cell> > board) {
	int tam = board.size();
	for (int i = 0; i < tam; ++i) {
		for (int j = 0; j < tam; ++j) {
			cout << board[i][j].getTile() << " "
					<< board[i][j].getDoor()->getNextState() << " " << "("
					<< board[i][j].getDoor()->getPosition()->getX() << ", "
					<< board[i][j].getDoor()->getPosition()->getY() << ") ";
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
bool pathExists(vector<vector<cell> > board, point *a, point *b) {
	bool res = true;
	if (board[b->getX()][b->getY()].getTile() == WALL) {
		res = false;
	// para 1 e 4
	} else if (a->getX() == b->getX() - 1 && a->getY() == b->getY()) {
		//a = 1
		if (board[a->getX()][a->getY()].getDoor()->getState() == 1
				&& board[b->getX()][b->getY() - 1].getTile() == WALL) {
			res = false;
		} else if (board[a->getX()][a->getY()].getDoor()->getState() == 4
				&& board[b->getX()][b->getY() + 1].getTile() == WALL) {
			res = false;
		}
	//para 2 e 3
	} else if (a->getX() == b->getX() && a->getY() == b->getY() + 1) {
		if (board[a->getX()][a->getY()].getDoor()->getState() == 2
				&& board[b->getX() + 1][b->getY()].getTile() == WALL) {
			res = false;
		} else if (board[a->getX()][a->getY()].getDoor()->getState() == 3
				&& board[b->getX() - 1][b->getY()].getTile() == WALL) {
			res = false;
		}
	}

	return res;
}

void findPath(vector<vector<cell> > board, point * s,
		vector<vector<int> > * Mexp) {
	vector<cell> lAdja = getAdjacentes(board, s);
	int tam_lAdja = lAdja.size();

	for (int i = 0; i < tam_lAdja; ++i) {
		point *v = new point(lAdja[i].getPosition()->getX(),
				lAdja[i].getPosition()->getY());
		if ((*Mexp)[v->getX()][v->getY()] == 0 && pathExists(board, s, v)) {
			(*Mexp)[v->getX()][v->getY()] = 1;
			findPath(board, v, Mexp);
		}
	}

}

int main() {
	int n;
	int a, b, c, d;
	while (scanf("%d", &n) == 1) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		point s(a, b);
		point f(c, d);

		vector<vector<cell> > board;
		vector<vector<int> > Mexp;
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

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				int cDoor;
				cin >> cDoor;
				point * p = new point(i, j);
				door * d = new door(cDoor, -1, p);
				board[i][j].setDoor(d);
			}
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				int nDoor;
				cin >> nDoor;
				door * d = new door(board[i][j].getDoor()->getState(), nDoor,
						board[i][j].getPosition());
				board[i][j].setDoor(d);
			}
		}

		/*cout << "=======INSTANCE=======\n";
		 printVectorInt(Mexp);*/

		findPath(board, &s, &Mexp);
		//cout << "\nAnother matrix\n";

		printVectorInt(Mexp);

	}

	return 0;
}

