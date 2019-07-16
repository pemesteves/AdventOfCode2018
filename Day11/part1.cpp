#include <iostream>
#include <thread>
#include <vector>
#include <utility>
#include <mutex>

using namespace std;

vector<vector<int>> total_power(300, vector<int>(300, 0));
int serial_number;

void calculate_total_power(int i, int j){
    int rackID = i + 10;
    int powerLevel = rackID * j;
    powerLevel += serial_number;
    powerLevel *= rackID;
    int digit = (powerLevel / 100) % 10;
    total_power[i][j] = digit - 5;
}

pair<int, int> position;
int largest_power;
mutex mtx;

void calculate_largest_power(int i, int j){
    int power = 0;
    for(int k = i; k < i + 3; k++){
        for(int l = j; l < j + 3; l++){
            power += total_power[k][l];
        }
    }

    mtx.lock();
    if(power > largest_power){
        position = make_pair(i, j);
        largest_power = power;
    }
    mtx.unlock();
}

int main(){
    cin >> serial_number;
    vector<thread> threads;

    for(int i = 0; i < 300; i++){
        for(int j = 0; j < 300; j++){
            threads.push_back(thread(calculate_total_power, i, j));
        }
    }

    for(int i = 0; i < threads.size(); i++){
       threads[i].join();
    }

    largest_power = 0;
    
    threads.clear();

    for(int i = 0; i <= 297; i++){
        for(int j = 0; j <= 297; j++){
            threads.push_back(thread(calculate_largest_power, i, j));
        }
    }

    for(int i = 0; i < threads.size(); i++){
       threads[i].join();
    }

    cout << position.first << "x" << position.second << ": power - " << largest_power << endl;
    system("pause");

    return 0;
}