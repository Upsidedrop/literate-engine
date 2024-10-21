#include <iostream>
#include <vector>
#include "Header.h"

using namespace std;

int main() {
	srand(time(NULL));

	Genome pa({
		{4,4,4,4},
		{4,4,4,4},
		{4,4,4,4},
		{4,4,4,4}
		});
	Genome ma({
		{8,8,8,8},
		{8,8,8,8},
		{8,8,8,8},
		{8,8,8,8}
		});
	Genome x = SubCrossover(pa, ma);
	x.Mutate();
	for (size_t i = 0; i < pa.genes.size(); i++)
	{
		for (size_t j = 0; j < pa.genes.size(); j++)
		{
			cout << x.genes[i][j];
		}
		cout << "\n";
	}

}
