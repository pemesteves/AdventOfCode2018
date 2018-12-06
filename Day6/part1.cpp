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

	vector<vector<unsigned>> mapa(500, vector<unsigned>(500));
	vector<pair<unsigned, unsigned>> v;
	unsigned first, second;
	unsigned counter = 1;
	while(!f.eof()){
		getline(f, line);
		first = stoi(line.substr(0, line.find(",")));
		second = stoi(line.substr(line.find(" ")+1));
		mapa[first][second] = counter;
		counter++;
	}
	
	for(size_t i = 0; i < 500; i++){
		for(size_t j = 0; j < 500){
			if
		}
	}


	cout << maxNumTimes << endl;

	char c;
	cin >> c;

	return 0;
}
