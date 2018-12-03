#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <string>

using namespace std;

int main(){
	ifstream f;
	f.open("input.txt");
	string line;
	unsigned xi, yi, width, height;
	map<pair<unsigned, unsigned>, unsigned> m;
	map<pair<unsigned, unsigned>, unsigned>::iterator it;
	pair<pair<unsigned, unsigned>, unsigned> p;
	pair<unsigned, unsigned> p1;


	while(!f.eof()){
		getline(f, line);
		line = line.substr(line.find("@") + 2);
		xi = stoi(line.substr(0, line.find(",")));
		line = line.substr(line.find(",")+1);
		yi = stoi(line.substr(0, line.find(" ")));
		line = line.substr(line.find(" ")+1);
		width = stoi(line.substr(0, line.find("x")));
		line = line.substr(line.find("x")+1);
		height = stoi(line);
		for(unsigned i = xi; i < xi+width; i++){
			for(unsigned j = yi; j < yi + height; j++){
				p1 = make_pair(i, j);
				it = m.find(p1);
				if (it == m.end()){
					p = make_pair(p1, 1);
					m.insert(p);
				}
				else{
					(*it).second++;
				}
			}
		}
	}

	unsigned count = 0;
	for(it = m.begin(); it != m.end(); it++){
		if ((*it).second > 1)
			count++;
	}
	cout << count << endl;
	char c;
	cin >> c;

	return 0;
}