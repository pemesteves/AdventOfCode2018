#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
	ifstream f;
	f.open("input.txt");
	string line, newLine;
	while(!f.eof()){
		getline(f, newLine);
		line += newLine;
	}

	unsigned initialSize = line.length();

	string::iterator it;

	do{
		initialSize = line.length();
		for(it = line.begin(); it != line.end() - 1; it++){
			if(((*it) != (*(it + 1))) && (toupper(*it) == toupper(*(it + 1)))){
				it = line.erase(it);
				it = line.erase(it);
				it--;
				break;
			} 
		}

	}while(initialSize != line.length());

	cout << line.length() << endl;

	char c;
	cin >> c;

	f.close();

	return 0;
}