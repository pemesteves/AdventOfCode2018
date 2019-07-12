#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Marble {
	int number;
	Marble* prev;
	Marble* next;
public: 
	Marble(int n, Marble* p, Marble* next) { number = n; prev = p; this->next = next; }
	Marble* getPrev() { return prev; }
	Marble* getNext() { return next; }
	int getNumber() { return number; }
	void setPrev(Marble* new_m) { this->prev = new_m; }
	void setNext(Marble* new_m) { this->next = new_m; }
};

Marble* removeMarble(Marble* m) {
	m->getNext()->setPrev(m->getPrev());
	m->getPrev()->setNext(m->getNext());
	return m;
}

Marble* insertAfter(Marble* m, int num) {
	Marble* marble = new Marble(num, m, m->getNext());
	m->getNext()->setPrev(marble);
	m->setNext(marble);
	return marble;
	
}

int main()
{
	ifstream f("input.txt");
	string line;
	getline(f, line);
	f.close();

	int num_players = stoi(line.substr(0, line.find(" ")));
	line = line.substr(line.find("worth"));
	line = line.substr(line.find(" ") + 1);
	int last_marble_points = stoi(line.substr(0, line.find(" ")))*100;

	vector<long long> players(num_players, 0);

	int marble_num = 1;
	Marble* curr = new Marble(0, NULL, NULL);
	curr->setNext(curr);
	curr->setPrev(curr);
	for (; marble_num <= last_marble_points; ) {
		for (int player = 0; player < num_players && marble_num <= last_marble_points; player++) {
			if (marble_num % 23 == 0) {
				players[player] += marble_num;
				Marble* m = removeMarble(curr->getPrev()->getPrev()->getPrev()->getPrev()->getPrev()->getPrev()->getPrev());
				players[player] += m->getNumber();
				curr = m->getNext();
			}
			else {
				curr = insertAfter(curr->getNext(), marble_num);
			}
			marble_num++;
		}
	}

	cout << "High Score: " << *max_element(players.begin(), players.end()) << endl;
	system("pause");

	return 0;
}
