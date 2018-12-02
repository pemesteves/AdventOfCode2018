#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <utility>

using namespace std;

int main(){
	ifstream f;
	f.open("input.txt");
	string line;
	map<char, unsigned int> m;
	map<char, unsigned int>::iterator it;
	pair<char, unsigned int> p;
	unsigned int two = 0, three = 0;
	bool foundTwo, foundThree;
	while(!f.eof()){
		foundTwo = false;
		foundThree = false;
		m.clear();
		getline(f, line);
		for(unsigned int i = 0; i < line.length(); i++){
			if((it = m.find(line[i])) != m.end()){
				(*it).second++;
			}
			else{
				p = make_pair(line[i], 1);
				m.insert(p);
			}
		}
		for(it = m.begin(); it != m.end(); it++){
			if ((*it).second == 2 && !foundTwo){
				two++;
				foundTwo = true;
			}
			else if ((*it).second == 3 && !foundThree){
				three++;
				foundThree = true;
			}
			else if (foundTwo && foundThree)
				break;
		}
	}

	cout << two << "; " << three << endl;
	cout << two*three;

	char c;
	cin >> c;

	return 0;
}