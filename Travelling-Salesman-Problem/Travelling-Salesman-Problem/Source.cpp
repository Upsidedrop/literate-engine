#include "Header.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int destinations = 20;

//O(n^2)
vector<vector<double>> RandCosts() {
	vector<vector<double>> res;
	for (size_t i = 0; i < destinations; i++)
	{
		res.push_back(vector<double>());
		for (size_t j = 0; j < destinations-i; j++)
		{
			res[i].push_back((double)(rand() % 50));
		}
	}
	return res;
}

//O(n)
int Genome::Rank(vector<int> input) {
	int highest = 0;
	for (size_t i = 1; i < input.size(); i++)
	{
		if (input[i] > input[highest] && !usedIDs[i])
		{
			highest = i;
		}
	}
	usedIDs[highest] = true;
	return highest;
}


//O(n^2)
void Genome::Evaluate(vector<vector<double>> connections) {
	int pos = 0;
	int lastPos = 0;
	usedIDs = vector<bool>(destinations);
	usedIDs[0] = true;
	for (int i = 0; i < destinations; i++) {
		pos = Rank(genes[pos]);

		if (pos < lastPos)
		{
			cost += connections[pos][connections.size() - 1 - lastPos];
		}
		else
		{
			cost += connections[lastPos][connections.size() - 1 - pos];
		}
		lastPos = pos;
	}
	cost += connections[0][connections.size() - 1 - lastPos];
}

//O(n^2)
Genome SubCrossover(Genome a, Genome b) {
	const int size = a.genes.size();
	
	vector<vector<int>> res(size, vector<int>(size,0));

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			res[i][j] = rand() % 2 == 0 ? a.genes[i][j] : b.genes[i][j];
		}
	}
	return Genome(res);
}

//O(n^2)
Genome::Genome() {
	for (size_t i = 0; i < destinations; i++)
	{
		genes.push_back(vector<int>());
		genes[i].push_back(0);
		for (size_t j = 1; j < destinations; j++)
		{
			genes[i].push_back(j==i? 0 : rand() % 20 + 50);

		}
	}
}

//O(n)
Genome::Genome(vector<vector<int>> a) {
	for (size_t i = 0; i < destinations; i++)
	{
		genes.push_back(vector<int>());
		genes[i].push_back(0);
		for (size_t j = 1; j < destinations; j++)
		{
			genes[i].push_back(j == i ? 0 : a[i][j]);

		}
	}
}

//O(n^2)
Genome AvCrossover(Genome a, Genome b) {
	const int size = a.genes.size();

	vector<vector<int>> res(size, vector<int>(size, 0));
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			res[i][j] = (a.genes[i][j] + b.genes[i][j]) / 2;
		}
	}
	return Genome(res);
}

//O(1)
void Genome::Mutate() {
	for (size_t i = 0; i < (rand() % destinations); i++)
	{
		genes[rand() % genes.size()][rand() % genes.size()] += (rand() % 41) * 2 - 40;
	}
}