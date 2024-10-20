#include <vector>

using namespace std;

class Genome {
	vector<int> usedIDs = {0};
	public:
		vector<vector<int>> genes;
		int Rank(vector<int> input);
		double Evaluate(vector<vector<double>> connections);
		Genome(vector<vector<int>> a);
};

Genome SubCrossover(Genome a, Genome b);
