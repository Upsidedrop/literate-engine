#include <iostream>
#include <vector>
#include <algorithm>
#include "Header.h"

using namespace std;


int Genome::Rank(vector<int> input) {

	int highest = 0;
	for (size_t i = 1; i < input.size(); i++)
	{
		if (input[i] > input[highest] && find(usedIDs.begin(), usedIDs.end(), i) == usedIDs.end())
		{
			highest = i;
		}
	}
	usedIDs.push_back(highest);
	return highest;
}

double Genome::Evaluate(vector<vector<double>> connections) {
	int pos = 0;
	int lastPos = 0;
	double res = 0;

	while (usedIDs.size() < connections.size()) {
		pos = Rank(genes[pos]);

		if (pos < lastPos)
		{
			res += connections[pos][connections.size() - 1 - lastPos];
		}
		else
		{
			res += connections[lastPos][connections.size() - 1 - pos];
		}
		lastPos = pos;
	}
	res += connections[0][connections.size() - 1 - lastPos];
	return res;
}

//vector<vector<int>> SubCrossover(vector<vector<int>> a, vector<vector<int>> b) {
//	
//}