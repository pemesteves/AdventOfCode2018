#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main(){
	ifstream f;
	f.open("input.txt");
	string line;
	vector<string> v;

	while(!f.eof()){
		getline(f, line);
		v.push_back(line);
	}

	unsigned int numChanges = 0;

	for(size_t i = 0; i < v.size(); i++){
		line = v[i];
		for(size_t j = i+1; j < v.size(); j++){
			numChanges = 0;
			for(unsigned int k = 0; k < line.length(); k++){
				if(numChanges > 1)
					break;
				if (line[k] != v[j][k]){
					numChanges++;
				}
			}
			if (numChanges > 1)
				continue;
			else{
				cout << line << endl;
				cout << v[j] << endl;
				for(unsigned int k = 0; k < line.length(); k++){
					if (line[k] != v[j][k]){
						continue;
					}
					else
						cout << line[k];
				}
				cout << endl;
				break;
			}
		}
		if(numChanges > 1)
			continue;
		else{
			cout << numChanges << endl;
			break;
		}
	}

	char c;
	cin >> c;

	return 0;
}