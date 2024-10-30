#include <iostream>
#include <vector>
#include "Header.h"

using namespace std;

const int targetGenomes = 100;
const int iterations = 100;

int main() {
	vector<vector<double>> inputs = {
		{100,5},{55,40},{84,80},{25,49},{134,55},{20,41},{102,24},{11,12},{77,28}
	};

	vector<vector<double>> costs = CostsFromVectors(inputs);
	srand(time(NULL));

	//vector<vector<double>> costs = RandCosts();

	best.cost = 100000;

	vector<Genome> genomes;
	for (size_t i = 0; i < targetGenomes; i++)
	{
		genomes.push_back(Genome());
	}
	Run(costs, targetGenomes, iterations, genomes);
	
	while (true) {
		char input;
		cout << "Continue? Y/N/R" << "\n";
		cin >> input;
		if (toupper(input) == 89)
		{
			Run(costs, targetGenomes, iterations, genomes);
		}
		if (toupper(input) == 82)
		{
			genomes.clear();
			for (size_t i = 0; i < targetGenomes; i++)
			{
				genomes.push_back(Genome());
			}
		}
		if (toupper(input) == 78)
		{
			cout << "Lowest cost was " << best.cost << "\n";
			cout << best.ToString();
			return 0;
		}
	}
}
