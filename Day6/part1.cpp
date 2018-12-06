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
	

	for(int i = 0; i < 500; i++){
		for(int j = 0; j < 500; j++){
			if(mapa[i][j] != 0)
				continue;
			else{
				int distance = 500*500;
				bool equalDistance = false;
				int distanceWhenEqual = 0;
				int position;
				for(size_t k = 0; k < v.size(); k++){
					if ((abs(v[k].first - j) + abs(v[k].second - i)) < distance){
						distance = abs(v[k].first - j) + abs(v[k].second - i);
						position = mapa[v[k].second][v[k].first];
					}
					else if ((abs(v[k].first - j) + abs(v[k].second - i)) == distance){
						equalDistance = true;
						distanceWhenEqual = distance;
					}
				}
				if(!equalDistance){
					mapa[i][j] = position;
				}
				else{
					if(distanceWhenEqual != distance){
						mapa[i][j] = position;
					}
				}
			}
		}
	}


	int maxNumTimes = 0;
	for(size_t k = 0; k < v.size(); k++){
		counter = mapa[v[k].second][v[k].first];
		int numTimes = 0;
		bool isInfinity = false;
		for(size_t i = 0; i < mapa.size(); i++){
			for(size_t j = 0; j < mapa[i].size(); j++) {
				if(mapa[i][j] == counter){
					if(i == 0 || j == 0 || i == 499 || j == 499){
						isInfinity = true;
						cout << counter << endl;
						break;
					}
					else{
						numTimes++;
					}
				}
			}
			if(isInfinity)
				break;
		}
		
		if(!isInfinity){
			if (numTimes > maxNumTimes)
				maxNumTimes = numTimes;
		}
	}
	cout << maxNumTimes << endl;

	char c;
	cin >> c;

	return 0;
}
