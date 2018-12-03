#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <string>

using namespace std;

bool isNotInVector(unsigned id, vector<unsigned> ids){
	for(size_t i = 0; i < ids.size(); i++){
		if(ids[i] == id)
			return false;
	}

	return true;
}

int main(){
	ifstream f;
	f.open("input.txt");
	string line;
	unsigned xi, yi, width, height, id;
	map<pair<unsigned, unsigned>, pair<unsigned, unsigned>> m;
	map<pair<unsigned, unsigned>, pair<unsigned, unsigned>>::iterator it;
	pair<pair<unsigned, unsigned>, pair<unsigned, unsigned>> p;
	pair<unsigned, unsigned> p1, p2;

	unsigned idDontOverlap = 0;
	bool overlap; 

	vector<unsigned> ids;

	while(!f.eof()){
		getline(f, line);
		id = stoi(line.substr(1, line.find(" ") - 1));
		line = line.substr(line.find("@") + 2);
		xi = stoi(line.substr(0, line.find(",")));
		line = line.substr(line.find(",")+1);
		yi = stoi(line.substr(0, line.find(" ")));
		line = line.substr(line.find(" ")+1);
		width = stoi(line.substr(0, line.find("x")));
		line = line.substr(line.find("x")+1);
		height = stoi(line);
		overlap = false;
		for(unsigned i = xi; i < xi + width; i++){
			for(unsigned j = yi; j < yi + height; j++){
				p1 = make_pair(i, j);
				it = m.find(p1);
				if (it == m.end()){
					p2 = make_pair(1, id);
					p = make_pair(p1, p2);
					m.insert(p);
				}
				else{
					(*it).second.first++;
					overlap = true;
				}
			}
		}
		if(!overlap)
			ids.push_back(id);
	}

	f.close();
	f.open("input.txt");
	while(!f.eof()){
		getline(f, line);
		id = stoi(line.substr(1, line.find(" ") - 1));
		if(isNotInVector(id, ids))
			continue;
		line = line.substr(line.find("@") + 2);
		xi = stoi(line.substr(0, line.find(",")));
		line = line.substr(line.find(",")+1);
		yi = stoi(line.substr(0, line.find(" ")));
		line = line.substr(line.find(" ")+1);
		width = stoi(line.substr(0, line.find("x")));
		line = line.substr(line.find("x")+1);
		height = stoi(line);
		overlap = false;
		for(unsigned i = xi; i < xi + width; i++){
			for(unsigned j = yi; j < yi + height; j++){
				p1 = make_pair(i, j);
				it = m.find(p1);
				if(it != m.end()){
					if((*it).second.second == id && !((*it).second.first > 1))
						continue;
					else{
						overlap = true;
						break;
					}
				}
			}
		}
		if(!overlap){
			cout << id << endl;
		}
	}
	f.close();
	char c;
	cin >> c;

	return 0;
}
