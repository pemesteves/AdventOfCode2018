#include <vector>
#include <map>
#include <utility>
#include <iostream>
#include <fstream>
#include <string> 
#include <math.h>

using namespace std;

int main(){
	ifstream f;
	f.open("input.txt");
	string line;

	vector<vector<int>> mapa(500, vector<int>(500, 0));
	vector<pair<int, int>> v;
	pair<int, int> p;
	int first, second;
	int counter = 1;
	while(!f.eof()){
		getline(f, line);
		first = stoi(line.substr(0, line.find(",")));
		second = stoi(line.substr(line.find(" ")+1));
		p = make_pair(first, second);
		v.push_back(p);
		mapa[second][first] = counter;
		counter++;
	}
	
	int totalDistance = 0;
	int regionSize = 0;
	

	for(int i = 0; i < 500; i++){
		for(int j = 0; j < 500; j++){
			totalDistance = 0;
			for(size_t k = 0; k < v.size(); k++){
				totalDistance += abs(v[k].first - j) + abs(v[k].second - i);
			}
			if(totalDistance < 10000)
				regionSize++;	
		}
	}
	cout << regionSize << endl;

	char c;
	cin >> c;

	return 0;
}
