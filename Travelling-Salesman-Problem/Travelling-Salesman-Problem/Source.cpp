#include <iostream>
#include <vector>
#include <algorithm>
#include "Header.h"

using namespace std;

//O(n^2)
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

//O(n)
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

//O(n^2)
Genome SubCrossover(Genome a, Genome b) {
	const int size = a.genes.size();
	
	vector<vector<int>> res(size, vector<int>(size,0));
	vector<vector<int>>* temp;

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			temp = rand() % 2 == 0 ? &(a.genes) : &(b.genes);
			res[i][j] = (*temp)[i][j];
		}
	}
	return Genome(res);
}

//O(1)
Genome::Genome(vector<vector<int>> a) {
	genes = a;
}