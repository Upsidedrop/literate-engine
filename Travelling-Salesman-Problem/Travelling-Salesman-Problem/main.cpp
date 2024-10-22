#include <iostream>
#include <vector>
#include "Header.h"

using namespace std;

int main() {
	srand(time(NULL));

	vector<vector<double>> costs = RandCosts();

	vector<Genome> genomes;
	vector<Genome> survivors;
	double average = 0;
	genomes.push_back(Genome());
	genomes.push_back(Genome());
	genomes.push_back(Genome());
	genomes.push_back(Genome());
	genomes.push_back(Genome());
	genomes.push_back(Genome());
	genomes.push_back(Genome());
	for (Genome& g : genomes) {
		g.Evaluate(costs);
		average += g.cost;
	}
	average /= genomes.size();
	for (Genome g : genomes) {
		if (g.cost < average)
		{
			survivors.push_back(g);
		}
	}
}
