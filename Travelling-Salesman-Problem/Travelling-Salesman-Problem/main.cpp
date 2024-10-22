#include <iostream>
#include <vector>
#include "Header.h"

using namespace std;

const int targetGenomes = 100;

int main() {
	srand(time(NULL));

	vector<vector<double>> costs = RandCosts();

	vector<Genome> genomes;
	for (size_t i = 0; i < targetGenomes; i++)
	{
		genomes.push_back(Genome());
	}
	for (size_t j = 0; j < 1000; j++)
	{
		double average = 0;
		for (Genome& g : genomes) {
			g.Evaluate(costs);
			average += g.cost;
		}
		average /= genomes.size();

		vector<Genome> survivors;
		for (Genome g : genomes) {
			if (g.cost <= average)
			{
				survivors.push_back(g); 
			}
		}
		cout << average << "\n";
		genomes.clear();
		for (size_t i = 0; i < targetGenomes; i++)
		{
			genomes.push_back(
				SubCrossover
				(survivors[rand() % survivors.size()],
					survivors[rand() % survivors.size()]));
		}
		////speciation may be necessary for this to be effective
		genomes[rand() % targetGenomes].Mutate();
	}
}
