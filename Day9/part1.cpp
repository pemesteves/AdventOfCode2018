#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ifstream f("input.txt");
    string line;
    getline(f, line);
    f.close();

    int num_players = stoi(line.substr(0, line.find(" ")));
    line = line.substr(line.find("worth"));
    line = line.substr(line.find(" ") + 1);
    int last_marble_points = stoi(line.substr(0, line.find(" ")));

    vector<int> marbles = {0};
    vector<int> players(num_players, 0);
    vector<int>::iterator it = marbles.end();

    int marble_num = 1;
    int player = 0;

    while(marble_num <= last_marble_points){
        if(marble_num % 23 == 0){
            players[player] += marble_num;
            for(int i = 0; i <= 8; i++){
                it--;
            }
            players[player] += *it;
            it = marbles.erase(it);
            it++; it++;
        }
        else if(it == marbles.end()){
            marbles.push_back(marble_num);
            it = marbles.begin();
            it++;
        }else{
           it = marbles.insert(it, marble_num);
           it++; it++;
        }
        marble_num++;
        player = (player+1)%num_players;
    }
    
    cout << "High Score: " << *max_element(players.begin(),players.end()) << endl; 
    system("pause");

    return 0;
}
