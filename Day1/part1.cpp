#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ifstream f;
	f.open("input.txt");
	int change, currentFrequency = 0;
	while(!f.eof()){
		f >> change;
		cout << "Current frequency " << currentFrequency << ", ";
		cout << "change of " << change << "; ";
		currentFrequency += change;
		cout << "resulting frequency " << currentFrequency << "." << endl;
	}
	char c;
	cin >> c;
	return 0;
}
