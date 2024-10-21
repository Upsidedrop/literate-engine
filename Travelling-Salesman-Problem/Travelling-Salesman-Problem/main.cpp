#include <iostream>
#include <vector>
#include "Header.h"

using namespace std;

int main() {
	srand(time(NULL));

	Genome pa({
		{0,6,7,12},
		{0,0,7,9},
		{0,4,0,6},
		{0,5,8,0}
		});

	vector<vector<double>> costs = {
		{1,2,3,4},
		{5,6,7},
		{8,9},
		{10}

	};
	Genome g;
	for (size_t i = 0; i < g.genes.size(); i++)
	{
		for (int x : g.genes[i]) {
			cout << x << " ";
		}
		cout << "\n";
	}
}
