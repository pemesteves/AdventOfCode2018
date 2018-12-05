#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

	vector<unsigned> v;
	v.resize(26, 0);

	char initialLetter = 'A', letter;

	newLine = line;
	
	for(size_t counter = 0; counter < v.size(); counter++){
		letter = initialLetter + counter;
		line = newLine;
		do{
			initialSize = line.length();
			for(it = line.begin(); it != line.end(); it++){
				if(toupper(*it) == letter){
					it = line.erase(it);
					it--;
				} 
			}
		}while(initialSize != line.length());
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

		v[counter] = line.length();
	}

	unsigned minimunSize = -1;

	for(size_t i = 0; i < v.size(); i++){
		if (v[i] < minimunSize)
			minimunSize = v[i];
	}


	cout << minimunSize << endl;

	char c;
	cin >> c;

	f.close();

	return 0;
}