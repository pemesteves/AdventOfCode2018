#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

unsigned parseInfo(string &info);

int main()
{
    ifstream f("input.txt");
    string file_info;
    getline(f, file_info);
    f.close();
    unsigned total = parseInfo(file_info);

    cout << total << endl;
    system("pause");

    return 0;
}

unsigned parseInfo(string &info)
{
    unsigned total = 0;
    int childs, metadata;
    childs = stoi(info.substr(0, info.find(" ")));
    info = info.substr(info.find(" ") + 1);
    metadata = stoi(info.substr(0, info.find(" ")));
    info = info.substr(info.find(" ") + 1);

    if (childs != 0)
    {
        vector<unsigned> child_meta(childs, 0);
        int meta = 0;

        for (int i = 0; i < childs; i++)
        {
            child_meta[i] = parseInfo(info);
        }

        for (int i = 0; i < metadata; i++)
        {
            meta = stoi(info.substr(0, info.find(" ")));
            info = info.substr(info.find(" ") + 1);

            if (meta == 0 || meta > childs)
                continue;
            else
            {
                total += child_meta[meta - 1];
            }
        }
    }
    else
    {
        for (int i = 0; i < metadata; i++)
        {
            total += stoi(info.substr(0, info.find(" ")));
            info = info.substr(info.find(" ") + 1);
        }
    }

    return total;
}