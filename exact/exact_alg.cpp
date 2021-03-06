#include <iostream>
#include <cstdio>
#include "../classes/point.h"
#include "../classes/door.h"
#include "../classes/cell.h"
#include "../classes/bitlib.h"
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
typedef vector <vector <vector <bool> > > vvvb;


void printPoint(point * p) {
	cout << "(" << p->getX() << ", " << p->getY() << ") ";
}

void printDoors(vector<vector<door> > doors) {
	int tam = doors.size();
	cout << "TM: " << tam << endl;
	for (int i = 0; i < tam; ++i) {
		for (int j = 0; j < tam; ++j) {
			if (doors[i][j].getId() != -1) {
				cout << doors[i][j].getId() << "[" << doors[i][j].getState() << "/"
					<< doors[i][j].getNextState() << "] ";
			} else {
					cout << " [" << doors[i][j].getState() << "/"
					<< doors[i][j].getNextState() << "] ";
			}

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

/**
 * receb como parametro 2 pontos a e b, respectivamente origente e destino, verifica-se a  
 * possibilidade de se passar de a para b, e retorna o ponto final do bombeiro.
 */

bool canMove(vector<vector<cell> > board, vector<vector<door> > doors, point *s, point *f) {

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

/*struct verticeComparator
{
    bool operator()(ic const &v1, ic const &v2)
    {
        return v1.first < v2.first;
    }
};*/

/*typedef std::set<ic, verticeComparator> JobSet;

int dijkstra(vvc board, vvd doors, point * s, vector<vvi> graph) {
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
		/*pega os adjacentes de c em board com as configura��es
		poss�veis de portas provocadas por tais movimentos
		//vector<ic> adjs = getAdjacentes(board, doors, c);
		

	}

	return 0;
}*/


/** v�rtice {configura��o atual de portas, cell}
todo peso entre duas celulas c1 e c2 � 1, 
desde que se possa ir de c1 para c2 */
typedef pair<int, point> ic;
/*
 * Move door, 0 its first state, 1 second state. If state is 0, go to 1, and from 1 to 0, otherwise.
 * It returns the representation number after switch bit. 
 *
int moveDoorByBit(int currentConfig, int dId) {
	int newConfig;
	if (bitOn(currentConfig, dId)) {
		newConfig = setBitTo0(currentConfig, dId);
	} else {
		newConfig = setBitTo1(currentConfig, dId);
	}
	return newConfig;
}*/

/*
 * It returns the current according with doors matrix
 */
/*int getConfig(vvd originalDoors, vvd newDoors) {
	int n = originalDoors.size();
	int newConfig = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (originalDoors[i][j].getState() != newDoors[i][j].getState()) {
				newConfig = setBitTo1(newConfig, originalDoors[i][j].getId());
				cout << "here\n";
			}
		}
	}
	cout << "This Config: " << newConfig << endl;
	return newConfig;
}*/

/*
 * It returns the possible configurations after move from s to f
 */
ii getConfig(vvc board, vvd doors, point s, point f, int currentConfig) {
	vi configs;
	ii configuration(-1, -1);
	int configRes = currentConfig;
	//cout << "entrou: " << s.getX() <<", " << s.getY() << " -> " << f.getX() <<", " << f.getY() << " cur : " << currentConfig << endl;
	if (s.getDirection(&f) == LEFT || s.getDirection(&f) == RIGHT) {
		//cout << "Aqui 1\n";
		point pUP;
		point pDOWN;
		if (s.getDirection(&f) == RIGHT) {
			pUP = *(s.getDoorUR());
			pDOWN = *(s.getDoorDR());
			//cout << "Indo para a direita\n";
		} else {
			pUP = *(f.getDoorUR());
			pDOWN = *(f.getDoorDR());
		}

		int idDoor = -1;

		if (doors[pUP.getX()][pUP.getY()].getState() == 3) {
			idDoor = doors[pUP.getX()][pUP.getY()].getId();
		} else if (doors[pDOWN.getX()][pDOWN.getY()].getState() == 2) {
			//cout << "A porta � 2\n";
			idDoor = doors[pDOWN.getX()][pDOWN.getY()].getId();
		} 

		//cout << "id: " << idDoor << endl;
		if (idDoor != -1) {
			// move door, 0 its first state, 1 second state. If state is 0, go to 1, and from 1 to 0, otherwise.
			configRes = flipBit(configRes, idDoor);
			//configs.push_back(configRes);
			//cout << "config: " << idDoor << endl;
		} 

		//configs.push_back(configRes);
		configuration.first = configRes;

		if (configRes == currentConfig) {
			cout << "bug is here\n";
			if (doors[pUP.getX()][pUP.getY()].getState() == 4) {
				idDoor = doors[pUP.getX()][pUP.getY()].getId();
			} else if (doors[pDOWN.getX()][pDOWN.getY()].getState() == 4) {
				idDoor = doors[pDOWN.getX()][pDOWN.getY()].getId();
			} 

			if (idDoor != -1) {

				//configs.push_back(flipBit(configRes, idDoor));
				configuration.second = flipBit(configRes, idDoor);
				//cout << "config: " << idDoor << endl;
			}
		}

	} else if (s.getDirection(&f) == UP || s.getDirection(&f) == DOWN) {
		//cout << "Aqui 2\n";
		point pLEFT;
		point pRIGHT;

		if (s.getDirection(&f) == DOWN) {
			pLEFT = *(s.getDoorDL());
			pRIGHT = *(s.getDoorDR());
		} else {
			pLEFT = *(f.getDoorDL());
			pRIGHT = *(f.getDoorDR());
		}

		int idDoor = -1;

		if (doors[pLEFT.getX()][pLEFT.getY()].getState() == 1) {
			idDoor = doors[pLEFT.getX()][pLEFT.getY()].getId();
		} else if (doors[pRIGHT.getX()][pRIGHT.getY()].getState() == 4) {
			idDoor = doors[pRIGHT.getX()][pRIGHT.getY()].getId();
		} 

		if (idDoor != -1) {
			configRes = flipBit(configRes, idDoor);
		}

		//configs.push_back(configRes);
		configuration.first = configRes;

		if (configRes == currentConfig) {
			cout << "No, is not, bug is here\n";
			if (doors[pLEFT.getX()][pLEFT.getY()].getState() == 2) {
				idDoor = doors[pLEFT.getX()][pLEFT.getY()].getId();
			} else if (doors[pRIGHT.getX()][pRIGHT.getY()].getState() == 2) {
				idDoor = doors[pRIGHT.getX()][pRIGHT.getY()].getId();
			} 

			if (idDoor != -1) {
				//buga aqui
				int bitFlipped = flipBit(configRes, idDoor);
				cout << "CARAI: " << bitFlipped << endl;
				cout << "configuration: " << configuration.first << ", " << configuration.second << endl;
				//configs.push_back(bitFlipped);
				configuration.second = bitFlipped;
				cout << "Passa aqui\n";
			}
		}

	}
	cout << "Retorno de CONFIGS\n";

	/*for (int i = 0; i < 2; ++i) {
		if (vetor[i] != -1) {
			configs.push_back(vetor[i]);
		}
	}*/

	return configuration;
}

bool intervalTest(int n, point p) {
	return p.getX() >= 0 && p.getX() < n &&
		   p.getY() >= 0 && p.getY() < n;
}

vvd applyConfig(int nDoors, vvd doors, int currentConfig) {
	vvd newDoors = doors;
	vi _bitsOn = getBitsOn(currentConfig, nDoors);
	int k = 0;
	if (_bitsOn.size() > 0) {
		for (int i = 0; i < (int) doors.size(); ++i) {
			for (int j = 0; j < (int) doors.size(); ++j) {
				if (_bitsOn[k] == doors[i][j].getId()) {
					k++;
					newDoors[i][j].moveDoor();
					//cout << "was aplyed\n";
				}
			}
		}
	}

	return newDoors;
}

/*
 * It return adjacent list of a vertice
 * n - size of board (nxn)
 * m - number of doors
 * board - board of tiles, 
 * doors - board of doors
 */
vector<ic> getAdjacentes(int n, int m, ic vertice, vvc board, vvd doors) {
	vector<ic> adjs;

	point s = vertice.second;
	int currentConfig = vertice.first;
	vvd newDoors = applyConfig(m, doors, currentConfig);//problema aqui
	//vvd newDoors = doors;
	// left from s
	point f(s.getX(), s.getY() - 1); 

	//cout << "\n\nsaindo de (" << s.getX() << ", " << s.getY() <<") para chegar pela \n";
	//canMove should be get the actual configuration. 
	//I must be to do other function with this adaptation
	if (intervalTest(n, f) && canMove(board, newDoors, &s, &f)) {
		//cout << "Esquerda em (" << f.getX() << ", " << f.getY() <<")\n";
		ii configuration = getConfig(board, newDoors, s, f, currentConfig);

		if (configuration.first != -1) adjs.push_back(ic(configuration.first, f));
		if (configuration.second != -1) adjs.push_back(ic(configuration.second, f));
	} 
	//down from rigth
	f = point(s.getX(), s.getY() + 1);
	if (intervalTest(n, f) && canMove(board, newDoors, &s, &f)) {
		//cout << "Direita em (" << f.getX() << ", " << f.getY() <<")\n";
		ii configuration = getConfig(board, newDoors, s, f, currentConfig);

		if (configuration.first != -1) adjs.push_back(ic(configuration.first, f));
		if (configuration.second != -1) adjs.push_back(ic(configuration.second, f));
	} 
	//up from s
	f = point(s.getX() - 1, s.getY());
	if (intervalTest(n, f) && canMove(board, newDoors, &s, &f)) {
		//cout << "Cima em (" << f.getX() << ", " << f.getY() <<")\n";
		ii configuration = getConfig(board, newDoors, s, f, currentConfig);

		if (configuration.first != -1) adjs.push_back(ic(configuration.first, f));
		if (configuration.second != -1) adjs.push_back(ic(configuration.second, f));
	}
	//bottom from s
	f = point(s.getX() + 1, s.getY());
	if (intervalTest(n, f) && canMove(board, newDoors, &s, &f)) {
		//cout << "Baixo em (" << f.getX() << ", " << f.getY() <<")\n";
		ii configuration = getConfig(board, newDoors, s, f, currentConfig);

		if (configuration.first != -1) adjs.push_back(ic(configuration.first, f));
		if (configuration.second != -1) adjs.push_back(ic(configuration.second, f));
	}

	return adjs;
}

vector<vvi> BFS(int n, int nDoors, vvc board, vvd doors, point *s, vvvb graph) {
	cout << "aqui\n";
	vector <vvi> dist;
	int m = 1 << nDoors;// doors combinations number
	//setup sizes w x h x d
	dist.resize(n);
	for (int i = 0; i < n; ++i) {
		dist[i].resize(n);
		for (int j = 0; j < n; ++j) {
			//dist[i][j].resize(1 << nDoors);
			dist[i][j].assign(m, INT_MAX);
		}
	}

	dist[s->getX()][s->getY()][0] = 0; // dist from s to s is 0
	queue<ic> q; 
	q.push(ic(0, *s));
	graph[s->getX()][s->getY()][0] = true;
	//int w = 0;
	while (!q.empty()) {
		ic u = q.front(); 
		q.pop();
		//cout << ++w << endl;
		//cout << "antes de getAdjacentes\n" << endl;
		vector<ic> adjs = getAdjacentes(n, nDoors, u, board, doors);
		//cout << "Depois de getAdjacentes\n" << endl;
		//cout << "(" << u.second.getX() << ", " << u.second.getY() << ", " << u.first << ") - ";
		//cout << "Size adjs: " <<  adjs.size() << endl;
		for (int i = 0; i < adjs.size(); ++i) {
			ic v = adjs[i];
			//add board teste here? When tile is 1 == WALL ?
			//cout << "v(" << v.second.getX() << ", " << v.second.getY() << ", " << v.first << "), ";
			if (graph[v.second.getX()][v.second.getY()][v.first] == false) {
				graph[v.second.getX()][v.second.getY()][v.first] = true;
				dist[v.second.getX()][v.second.getY()][v.first] = dist[u.second.getX()][u.second.getY()][u.first] + 1;
				q.push(v);
			}
		}
		//cout << "chegou no final\n";
	} 
	return dist;
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

		vector<vector<vector<bool> > > MExploit;

		// Set up sizes. (HEIGHT x WIDTH)
		MExploit.resize(n);
		for (int i = 0; i < n; ++i) {
			MExploit[i].resize(n);

			for (int j = 0; j < n; ++j) {
				MExploit[i][j].resize(1 << nDoors);
				MExploit[i][j].assign(n, false);
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
				if (cDoor != 0) idDoor = id++;
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

		//TESTE==============================
		//getAdjacentes(n, nDoors, u, board, doors);
		/*int x = 4, y = 5, z = 0;
		vector<ic> ics = getAdjacentes(n, nDoors, ic(z, point(x, y)), board, doors);
		for (int i = 0; i < (int) ics.size(); ++i) {
			cout << "(" << ics[i].second.getX() << ", " << ics[i].second.getY() << ", " << ics[i].first << ")" << endl;
		}*/
		//==============================
		
		vector<vvi> res = BFS(n, nDoors, board, doors, &s, MExploit);
		int min = INT_MAX;
		for (int i = 0; i < 1 << nDoors; ++i) {
			if (res[f.getX()][f.getY()][i] < min) {
				min = res[f.getX()][f.getY()][i];
				cout << "alegria\n";
			}
		}
		cout << min << endl;

		/*cout << canMove(board, doors, new point(0, 0), new point(0, 1)) << endl;
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
		}*/
	}

	return 0;
}
