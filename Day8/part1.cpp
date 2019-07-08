#include <fstream>
#include <string>
#include <iostream>

using namespace std;

unsigned parseInfo(string &info);

int main(){
    ifstream f("input.txt");
    string file_info;
    getline(f, file_info);
    f.close();
    unsigned total = parseInfo(file_info);
    
    cout << total << endl;
    system("pause");

    return 0;
}

unsigned parseInfo(string &info){
    unsigned total = 0;
    int childs, metadata;
    childs = stoi(info.substr(0, info.find(" ")));
    info = info.substr(info.find(" ") + 1);
    metadata = stoi(info.substr(0, info.find(" ")));
    info = info.substr(info.find(" ") + 1);
    
    for(int i = 0; i < childs; i++){
        total += parseInfo(info);
    }

    for(int i = 0; i < metadata; i++){
        total += stoi(info.substr(0, info.find(" ")));
        info = info.substr(info.find(" ") + 1);
    }
    
    return total;
}