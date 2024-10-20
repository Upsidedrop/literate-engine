#include <vector>

using namespace std;

//vector<vector<int>> SubCrossover(vector<vector<int>> a, vector<vector<int>> b);

class Genome {
	vector<int> usedIDs = {0};
	public:
		vector<vector<int>> genes;
		int Rank(vector<int> input);
		double Evaluate(vector<vector<double>> connections);
};
