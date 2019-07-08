#include <unordered_map>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class compareFunction
{
public:
  bool operator() (const char &c1, const char &c2) const
  {
    if (c1 > c2)
        return true;
    return false;
  }
};

int main()
{
    string line;
    ifstream f;
    f.open("input.txt");
    char first, second;
    unordered_map<char, vector<char>> letters;
    pair<char, vector<char>> p1;
    unordered_map<char, vector<char>>::iterator it;
    unordered_map<char, bool> appears;
    pair<char, bool> p2;
    unordered_map<char, bool>::iterator it1;

    while (!f.eof())
    {
        getline(f, line);
        line = line.substr(line.find(" ") + 1);
        first = line[0];
        line = line.substr(line.find("step"));
        line = line.substr(line.find(" ") + 1);
        second = line[0];
        if ((it = letters.find(first)) == letters.end()) //Didn't found the letter
        { 
            vector<char> new_vector;
            new_vector.push_back(second);
            p1 = make_pair(first, new_vector);
            letters.insert(p1);
        }
        else
        { //Found the letter
            (*it).second.push_back(second);
        }

        if((it = letters.find(second)) == letters.end()){
            letters.insert(make_pair(second, vector<char>()));
        }

        if ((it1 = appears.find(first)) == appears.end())
        {
            p2 = make_pair(first, false);
            appears.insert(p2);
        }

        if ((it1 = appears.find(second)) == appears.end())
        {
            p2 = make_pair(second, true);
            appears.insert(p2);
        }
        else
        {
            (*it1).second = true;
        }
    }

    priority_queue<char, vector<char>, compareFunction> q;

    for (it1 = appears.begin(); it1 != appears.end(); )
    {
        if(!(*it1).second){
            q.push((*it1).first);
            it1 = appears.erase(it1);
        }
        else{
            it1++;
        }
    }

    string result = "";

    while(letters.size() > 0){
        char p_letter = q.top();
        q.pop();
        result += p_letter;
        it = letters.find(p_letter);
        vector<char> next_letters = (*it).second;
        letters.erase(it);
        for(int i = 0; i < next_letters.size(); i++){
            bool found_letter = false;
            for(it = letters.begin(); it != letters.end(); it++){
                for(int j = 0; j < (*it).second.size(); j++){
                    if((*it).second[j] == next_letters[i]){
                        found_letter = true;
                        break;
                    }
                }
                if(found_letter)
                    break;
            }
            if(!found_letter){
                q.push(next_letters[i]);
                it1 = appears.find(next_letters[i]);
                appears.erase(it1);
            }
        }
    }

    ofstream o("result_part1.txt");
    o << result << endl;
    o.close();

    return 0;
}