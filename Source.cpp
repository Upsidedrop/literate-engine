#include "Header.h"
//#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int destinations = 20;
Genome best;

//O(n^2)
string Genome::ToString(){
	string res = "0";
	
	usedIDs = vector<bool>(usedIDs.size(),false);
	for (size_t i = 0; i < destinations; i++)
	{
		int pos = 0;
		pos = Rank(genes[pos]);

		res.append(" - ");
		res.append(to_string(pos));
	}


	return res;
}

//O(n^2)
void Run(vector<vector<double>> costs, const int targetGenomes, const int iterations, vector<Genome>& genomes){
	for (size_t j = 0; j < iterations; j++)
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
				cout << g.cost << "\n";
			}
			if (g.cost < best.cost)
			{
				best = g;
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

//O(1)
double Magnitude(vector<double> vec){
	double res = 0;
	for(double val : vec){
		res += val * val;
	}
	return sqrt(res);
}

//O(1)
vector<double> SubtractVector(vector<double> vec1, vector<double> vec2){
	for (size_t i = 0; i < vec1.size(); i++)
	{
		vec1[i] -= vec2[i];
	}
	return vec1;
}

//O(1)
double Distance(vector<double> vec1, vector<double> vec2){
	return round(Magnitude(SubtractVector(vec1,vec2)));
}

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

vector<vector<double>> CostsFromVectors(vector<vector<double>> list){
	destinations = list.size();
	vector<vector<double>> res;
	for (int i = 0; i < destinations; i++)
	{
		vector<double> layer;
		int j = destinations-1;
		//No idea why I need this
		bool temp = true;
		while (temp)
		{
			layer.push_back(Distance(list[i],list[j]));
			j--;
			temp = j>=i;
		}
		res.push_back(layer);
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