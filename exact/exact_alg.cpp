#include <iostream>
#include <cstdio>
#include "../classes/point.h"
#include "../classes/door.h"
#include "../classes/cell.h"
#include "../classes/exploitElement.h"
#include <vector>
#include <queue>
#include <functional>
#include <climits>
#include <set>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<cell> vc;
typedef vector<door> vd;
typedef vector<vc> vvc;
typedef vector<vd> vvd;


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

void printVectorInt(vvi board) {
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

	//point *s = from->getPosition();
	//point *f = to->getPosition();

	bool canMove = false;
	if (board[f->getX()][f->getY()].getTile() == GROUND) {
		if (s->getDirection(f) == UP) {
			canMove = avalCanMove(doors, s->getDoorUR(), s->getDoorUL(), 4, 1, 2)
			 || ( doors[s->getDoorUR()->getX()][s->getDoorUR()->getY()].getState() != 4 
			 	&& doors[s->getDoorUL()->getX()][s->getDoorUL()->getY()].getState() != 1 );
		} else if (s->getDirection(f) == DOWN) {
			canMove = avalCanMove(doors, s->getDoorDL(), s->getDoorDR(), 1, 4, 3) 
			|| ( doors[s->getDoorDL()->getX()][s->getDoorDL()->getY()].getState() != 1 
			 	&& doors[s->getDoorDR()->getX()][s->getDoorDR()->getY()].getState() != 4 );
		} else if (s->getDirection(f) == RIGHT) {
			canMove = avalCanMove(doors, s->getDoorUR(), s->getDoorDR(), 3, 2, 1)
			|| ( doors[s->getDoorUR()->getX()][ s->getDoorUR()->getY()].getState() != 3 
			 	&& doors[s->getDoorDR()->getX()][ s->getDoorDR()->getY()].getState() != 2 );
		} else if (s->getDirection(f) == LEFT) {
			canMove = avalCanMove(doors, s->getDoorUL(), s->getDoorDL(), 3, 2, 4)
			|| ( doors[s->getDoorUL()->getX()][ s->getDoorUL()->getY()].getState() != 3 
			 	&& doors[s->getDoorDL()->getX()][ s->getDoorDL()->getY()].getState() != 2 );
		} 
	}
	return canMove;
}

int getDoorConfiguration(vvc board, vvd doors, cell *from, cell *to) {
	/*if (canMove(board, doors, from, to)) {

	}*/
}

/** vértice {configuração atual de portas, cell}
todo peso entre duas celulas c1 e c2 é 1, 
desde que se possa ir de c1 para c2 */
typedef pair<int, cell> ic;

struct verticeComparator
{
    bool operator()(ic const &v1, ic const &v2)
    {
        return v1.first < v2.first;
    }
};

typedef std::set<ic, verticeComparator> JobSet;

int dijkstra(vvc board, vvd doors,
		point * s, vector<vvi> graph) {
	int n = board.size();
	vvi dist(n, vi(n, INT_MAX));
	dist[s->getX()][s->getY()] = 0;
	priority_queue<ic, vector<ic>, verticeComparator> pq;
	pq.push( ic(0, board[s->getX()][s->getY()]) );

	while (!pq.empty()) {
		ic front = pq.top();
		pq.pop();

		int doorConfig = front.first;
		cell c = front.second;
		point * p = c.getPosition();
		//analizar if abaixo
		if (dist[p->getX()][p->getY()]) continue;
		/*pega os adjacentes de c em board com as configurações
		possíveis de portas provocadas por tais movimentos */
		//vector<ic> adjs = getAdjacentes(board, doors, c);
		

	}

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
				MExploit[i][j].resize(1 << nDoors);
				MExploit[i][j].assign(n, 0);
			}
		}

		/*for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				for (int k = 0; k < 1 << nDoors; k++) {
					cout << MExploit[i][j][k] << " ";
				}
				cout << "\n";
			}
			cout << "\n";
		}*/

		int id = 0;
		for (int i = 0; i < n + 1; ++i) {
			vector<door> line;
			for (int j = 0; j < n + 1; ++j) {
				int cDoor;
				cin >> cDoor;
				point * p = new point(i, j);
				//door (currenteState, nextState, point)
				int idDoor = -1;
				if (cDoor != 0) idDoor = ++id;
				door d(idDoor, cDoor, -1, p);
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
		//printVectorInt(Mexp);

		cout << canMove(board, doors, new point(0, 0), new point(0, 1)) << endl;
		cout << canMove(board, doors, new point(2, 1), new point(2, 2)) << endl;
		cout << "Start with your move: \n";
		int x1, y1, x2, y2;
		while (scanf("%d %d %d %d", &x1, &y1, &x2, &y2) == 4) {
			point *p1 = new point(x1, y1);
			point *p2 = new point(x2, y2);
			if (canMove(board, doors, p1, p2)) {
			cout << "Yes from ";
			} else {
			cout << "No from ";
			}
			printPoint(p1);
			cout << "to ";
			printPoint(p2);
			cout << endl;
		}
	}

	return 0;
}
