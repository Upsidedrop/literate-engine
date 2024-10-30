#include <vector>
#include <iostream>

using namespace std;

vector<vector<double>> RandCosts();
class Genome {
	vector<bool> usedIDs;
	public:
		double cost = 0;
		vector<vector<int>> genes;
		int Rank(vector<int> input);
		void Evaluate(vector<vector<double>> connections);
		Genome();
		Genome(vector<vector<int>> a);
		void Mutate();
		string ToString();
};

Genome SubCrossover(Genome a, Genome b);
Genome AvCrossover(Genome a, Genome b);

void Run(vector<vector<double>> costs, const int targetGenomes, const int iterations, vector<Genome>& genomes);
extern Genome best;