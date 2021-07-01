#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <iostream>

using namespace std;

vector<vector<int>> prefix_functions;

void compute_prefix_function(string pattern){
	int m = pattern.length();
	vector<int> pi(m);
	pi[0] = 0;
	int k = 0;

	for(int q = 1; q < m; q++){
		while(k > 0 && pattern[k+1] != pattern[q]){
			k = pi[k];
		}
		if(pattern[k+1] == pattern[q]){
			k++;
		}
		pi[q] = k;
	}

	prefix_functions.push_back(pi);
}

vector<int> kmpMatcher(string text, string pattern, int position) {
	int n = text.length();
	int m = pattern.length();
	vector<int> pi = prefix_functions[position];
	int q = 0;
	vector<int> matches;
	for(int i = 0; i < n; i++){
		while(q > 0 && pattern[q] != text[i]){
			q = pi[q-1];
		}
		if(pattern[q] == text[i])
			q++;
		if(q == m){
			matches.push_back(i);
			q = pi[q-1];
		}
	}

	return matches;
}

int main(){
    string initial;
    vector<pair<string, char>> productions;

    string line;
    ifstream f("input.txt");
    getline(f, line); //initial state
    line = line.substr(line.find(":")+2);
    initial = line;

    getline(f, line); //empty line

    while(!f.eof()){
        getline(f, line);
        productions.push_back(make_pair(line.substr(0, line.find(" ")), line[line.length()-1]));
    }
    
	for(int i = 0; i < productions.size(); i++){
		compute_prefix_function(productions[i].first);
	}

	for(int i = 0; i < 50; i++){
		initial.push_back('.');
	}

	string new_string(50, '.');
	initial.insert(0, new_string);

	new_string.clear();

	for(int i = 0; i < 20; i++){
		new_string = initial;
		for(int j = 0; j < productions.size(); j++){
			vector<int> v = kmpMatcher(initial, productions[j].first, j);
			for(int k = 0; k < v.size(); k++){
				new_string[v[k] - 2] = productions[j].second;
			}
		}
		initial = new_string;
	}
	
	unsigned total = 0;
	for(int i = 0; i < initial.length(); i++){
		cout << initial[i];
		if(initial[i] == '#')
			total++;
	}
	cout << total << endl;
    system("pause");

    return 0;
}