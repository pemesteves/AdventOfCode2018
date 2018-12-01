#include <iostream>
#include <fstream>
#include <map>
#include <utility>

using namespace std;

int main(){
	ifstream f;
	int change, currentFrequency = 0;
	map<int, int> m;
	pair<int, int> p;
	p = make_pair(currentFrequency, 1);
	bool notFound = true;
	while(notFound){
	 	f.open("input.txt");
		while(!f.eof()){
			f >> change;
			cout << "Current frequency " << currentFrequency << ", ";
			cout << "change of " << change << "; ";
			currentFrequency += change;
			cout << "resulting frequency " << currentFrequency << "." << endl;
			if(m.find(currentFrequency) != m.end()){
				notFound = false;
				break;
			}
			else{
				p = make_pair(currentFrequency, 1);
				m.insert(p);
			}
		}
		f.close();	
	}
	char c;
	cin >> c;
	return 0;
}