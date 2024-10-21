#include <vector>

using namespace std;

class Genome {
	int usedIDs = 1;
	public:
		vector<vector<int>> genes;
		int Rank(vector<int> input);
		double Evaluate(vector<vector<double>> connections);
		Genome(vector<vector<int>> a);
		void Mutate();
};

Genome SubCrossover(Genome a, Genome b);
Genome AvCrossover(Genome a, Genome b);
