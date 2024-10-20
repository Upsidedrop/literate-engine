#include <iostream>
#include <vector>
#include "Header.h"

using namespace std;

int main() {
	srand(time(NULL));

	Genome pa({
		{1,1,1,1},
		{1,1,1,1},
		{1,1,1,1},
		{1,1,1,1}
		});
	Genome ma({
		{15,15,15,15},
		{15,15,15,15},
		{15,15,15,15},
		{15,15,15,15}
		});
	Genome x = AvCrossover(pa, ma);
	for (size_t i = 0; i < pa.genes.size(); i++)
	{
		for (size_t j = 0; j < pa.genes.size(); j++)
		{
			cout << x.genes[i][j];
		}
		cout << "\n";
	}

}
