#include <iostream> 

using namespace std;

typedef struct tipo_aresta 
{
	unsigned int id; // id da aresta
	char cor; // cor da aresta A é livre e V não
	unsigned int dependencia; // indica quais cores elementos devem ter sua cor alterada
} aresta;

void print_aresta(aresta a) {
	cout << "(" << a.id << ", " << a.cor << ", " << a.dependencia << ")" << endl;  
}

typedef vector<vector<aresta>> graph;

int main() {
	int n;
	cin >> n;
	vector<aresta> line;
	graph g(n, line);

	for (int i = 0; i < n; ++i) {
		int m;
		cin >> m;
		for (int j = 0; j < m; ++j) {
			aresta a;
			cin >> a.id;
			cin >> a.cor;
			cin >> a.dependencia;
			g[i].push_back(a);
		}
	}
	return 0;
}