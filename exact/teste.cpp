#include <iostream>
#include <climits>

using namespace std;

int main() {
	for (int i = 0; i < INT_MAX; ++i)
	{
		cout << "teste\n";
		for (int j = 0; j < INT_MAX; ++j)
		{
			cout << "teste2\n";
		}
	}
	return 0;
}