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
	map<string, string> m;
	pair<string, string> p;

	string date, info;
	int i = 0;
	while(!f.eof()){
		getline(f, line);
		date = line.substr(1, line.find("]") - 1);
		line = line.substr(line.find("]")+2);
		info = line;
		p = make_pair(date, info);
		m.insert(p);	
	}
	f.close();
	unsigned id;
	unsigned fallSleep, awake;
	map<unsigned, vector<unsigned>> m1;
	pair<unsigned, vector<unsigned>> p1;
	map<unsigned, vector<unsigned>>::iterator it1;
	vector<unsigned> v(60, 0); 

	for(map<string, string>::iterator it = m.begin(); it !=m.end(); it++){
		info = (*it).second; //We only need the id of the guard
		if(info.substr(0, info.find(" ")) == "Guard"){
		
			info = info.substr(info.find("#") + 1);
			id = stoi(info.substr(0, info.find(" ")));
		}
		else {
			it--;
		}

		it++; //Jump to next string
		info = (*it).second;
		if(info.substr(0, info.find(" ")) == "Guard"){
		
			it--;
			continue;
		}
		else{

			date = (*it).first;

			date = date.substr(date.find(":")+1);

			fallSleep = stoi(date);

			it++; //Jump to next string

			date = (*it).first;

			date = date.substr(date.find(":")+1);

			awake = stoi(date);

			it1 = m1.find(id);
			if(it1 == m1.end()){
				v.clear();
				v.resize(60, 0);

				for(size_t i = 0; i < v.size(); i++){
					if(i>= fallSleep && i < awake){
						v[i] = 1;
					}
					else{
						v[i] = 0;
					}
				}
				p1 = make_pair(id, v);
				m1.insert(p1);
			}
			else{
				for(size_t i = fallSleep; i < awake; i++){
						(*it1).second[i]++;
				}
			}
		}
	}

	unsigned numMinutesSleeping = 0;
	id = 0;
	unsigned minute = 0;

	for(it1 = m1.begin(); it1 != m1.end(); it1++){
		unsigned internalMinute = 0;
		unsigned numCounter = 0;
		for(size_t i = 0; i < (*it1).second.size(); i++){
			if ((*it1).second[i] > numCounter){
				numCounter = (*it1).second[i];
				internalMinute = i;
			}
		}

		if(numCounter > numMinutesSleeping){
			id = (*it1).first;
			numMinutesSleeping = numCounter;
			minute = internalMinute;
		}
	}

	cout << id << endl;
	cout << minute << endl;
	cout << id*minute << endl;

	char c;
	cin >> c;
	return 0;
}