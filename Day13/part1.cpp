#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

int main()
{
    vector<vector<char>> map;
    vector<vector<char>> cart_map;
    vector<pair<int, int>> cart_positions;
    vector<string> cart_dir_intersect;
    vector<char> map_line;
    vector<char> cart_map_line;

    ifstream f("input.txt");
    string line;
    int line_number = 0;
    while (!f.eof())
    {
        map_line.clear();
        cart_map_line.clear();
        getline(f, line);
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '>' || line[i] == '<')
            {
                map_line.push_back('-');
                cart_map_line.push_back(line[i]);
                cart_positions.push_back(make_pair(line_number, i));
                cart_dir_intersect.push_back("left");
            }
            else if (line[i] == '^' || line[i] == 'v')
            {
                map_line.push_back('|');
                cart_map_line.push_back(line[i]);
                cart_positions.push_back(make_pair(line_number, i));
                cart_dir_intersect.push_back("left");
            }
            else
            {
                map_line.push_back(line[i]);
                cart_map_line.push_back('.');
            }
        }
        line_number++;
        map.push_back(map_line);
        cart_map.push_back(cart_map_line);
    }

    f.close();
    int x = 0, y = 0;
    pair<int, int> crash = make_pair(-1, -1);

    while (true)
    {
        for (int i = 0; i < cart_positions.size(); i++)
        {
            x = cart_positions[i].first;
            y = cart_positions[i].second;
            if (map[x][y] == '+')
            {
                if (cart_map[x][y] == '>')
                {
                    if (cart_dir_intersect[i] == "left")
                    {
                        if (cart_map[x - 1][y] != '.')
                        {
                            crash = make_pair(x - 1, y);
                            break;
                        }
                        cart_positions[i] = make_pair(x - 1, y);
                        cart_map[x - 1][y] = '^';
                        cart_dir_intersect[i] = "straight";
                    }
                    else if (cart_dir_intersect[i] == "straight")
                    {
                        if (cart_map[x][y + 1] != '.')
                        {
                            crash = make_pair(x, y + 1);
                            break;
                        }
                        cart_positions[i] = make_pair(x, y + 1);
                        cart_map[x][y + 1] = '>';
                        cart_dir_intersect[i] = "right";
                    }
                    else if (cart_dir_intersect[i] == "right")
                    {
                        if (cart_map[x + 1][y] != '.')
                        {
                            crash = make_pair(x + 1, y);
                            break;
                        }
                        cart_positions[i] = make_pair(x + 1, y);
                        cart_map[x + 1][y] = 'v';
                        cart_dir_intersect[i] == "left";
                    }
                }
                else if (cart_map[x][y] == 'v')
                {
                    if (cart_dir_intersect[i] == "left")
                    {
                        if (cart_map[x][y+1] != '.')
                        {
                            crash = make_pair(x , y+1);
                            break;
                        }
                        cart_positions[i] = make_pair(x, y+1);
                        cart_map[x][y+1] = '>';
                        cart_dir_intersect[i] = "straight";
                    }
                    else if (cart_dir_intersect[i] == "straight")
                    {
                        if (cart_map[x+1][y] != '.')
                        {
                            crash = make_pair(x+1, y);
                            break;
                        }
                        cart_positions[i] = make_pair(x+1, y);
                        cart_map[x+1][y ] = 'v';
                        cart_dir_intersect[i] = "right";
                    }
                    else if (cart_dir_intersect[i] == "right")
                    {
                        if (cart_map[x][y-1] != '.')
                        {
                            crash = make_pair(x, y-1);
                            break;
                        }
                        cart_positions[i] = make_pair(x, y-1);
                        cart_map[x][y-1] = '<';
                        cart_dir_intersect[i] == "left";
                    }
                }
                else if (cart_map[x][y] == '<')
                {
                    if (cart_dir_intersect[i] == "left")
                    {
                        if (cart_map[x+1][y] != '.')
                        {
                            crash = make_pair(x+1 , y);
                            break;
                        }
                        cart_positions[i] = make_pair(x+1, y);
                        cart_map[x+1][y] = 'v';
                        cart_dir_intersect[i] = "straight";
                    }
                    else if (cart_dir_intersect[i] == "straight")
                    {
                        if (cart_map[x][y-1] != '.')
                        {
                            crash = make_pair(x, y-1);
                            break;
                        }
                        cart_positions[i] = make_pair(x, y-1);
                        cart_map[x][y-1] = '<';
                        cart_dir_intersect[i] = "right";
                    }
                    else if (cart_dir_intersect[i] == "right")
                    {
                        if (cart_map[x - 1][y] != '.')
                        {
                            crash = make_pair(x - 1, y);
                            break;
                        }
                        cart_positions[i] = make_pair(x - 1, y);
                        cart_map[x - 1][y] = '^';
                        cart_dir_intersect[i] == "left";
                    }
                }
                else if (cart_map[x][y] == '^')
                {
                    if (cart_dir_intersect[i] == "left")
                    {
                        if (cart_map[x][y-1] != '.')
                        {
                            crash = make_pair(x , y-1);
                            break;
                        }
                        cart_positions[i] = make_pair(x, y-1);
                        cart_map[x][y-1] = '<';
                        cart_dir_intersect[i] = "straight";
                    }
                    else if (cart_dir_intersect[i] == "straight")
                    {
                        if (cart_map[x-1][y] != '.')
                        {
                            crash = make_pair(x-1, y);
                            break;
                        }
                        cart_positions[i] = make_pair(x-1, y);
                        cart_map[x-1][y ] = '^';
                        cart_dir_intersect[i] = "right";
                    }
                    else if (cart_dir_intersect[i] == "right")
                    {
                        if (cart_map[x][y+1] != '.')
                        {
                            crash = make_pair(x, y+1);
                            break;
                        }
                        cart_positions[i] = make_pair(x, y+1);
                        cart_map[x][y+1] = '>';
                        cart_dir_intersect[i] == "left";
                    }
                }
            }
            else if(map[x][y] == '\\'){
                if (cart_map[x][y] == '>')
                {
                    if (cart_map[x + 1][y] != '.')
                    {
                        crash = make_pair(x + 1, y);
                        break;
                    }
                    cart_positions[i] = make_pair(x + 1, y);
                    cart_map[x + 1][y] = 'v';
                }
                else if (cart_map[x][y] == 'v')
                {
                    if (cart_map[x][y+1] != '.')
                    {
                        crash = make_pair(x, y+1);
                        break;
                    }
                    cart_positions[i] = make_pair(x, y+1);
                    cart_map[x][y+1] = '>';
                }
                else if (cart_map[x][y] == '<')
                {
                    if (cart_map[x-1][y] != '.')
                    {
                        crash = make_pair(x-1, y);
                        break;
                    }
                    cart_positions[i] = make_pair(x-1, y);
                    cart_map[x-1][y] = '^';
                }
                else if (cart_map[x][y] == '^')
                {
                    if (cart_map[x][y-1] != '.')
                    {
                        crash = make_pair(x, y-1);
                        break;
                    }
                    cart_positions[i] = make_pair(x, y-1);
                    cart_map[x][y-1] = '<';
                }
            }
            else if(map[x][y] == '/'){
                if (cart_map[x][y] == '>')
                {
                    if (cart_map[x - 1][y] != '.')
                    {
                        crash = make_pair(x - 1, y);
                        break;
                    }
                    cart_positions[i] = make_pair(x - 1, y);
                    cart_map[x - 1][y] = '^';
                }
                else if (cart_map[x][y] == 'v')
                {
                    if (cart_map[x][y-1] != '.')
                    {
                        crash = make_pair(x, y-1);
                        break;
                    }
                    cart_positions[i] = make_pair(x, y-1);
                    cart_map[x][y-1] = '<';
                }
                else if (cart_map[x][y] == '<')
                {
                    if (cart_map[x+1][y] != '.')
                    {
                        crash = make_pair(x+1, y);
                        break;
                    }
                    cart_positions[i] = make_pair(x+1, y);
                    cart_map[x+1][y] = 'v';
                }
                else if (cart_map[x][y] == '^')
                {
                    if (cart_map[x][y+1] != '.')
                    {
                        crash = make_pair(x, y+1);
                        break;
                    }
                    cart_positions[i] = make_pair(x, y+1);
                    cart_map[x][y+1] = '>';
                }
            }
            else if(map[x][y] == '-'){
               if (cart_map[x][y] == '>')
                {
                    if (cart_map[x][y+1] != '.')
                    {
                        crash = make_pair(x, y+1);
                        break;
                    }
                    cart_positions[i] = make_pair(x, y+1);
                    cart_map[x][y+1] = '>';
                } 
                else if (cart_map[x][y] == '<')
                {
                    if (cart_map[x][y-1] != '.')
                    {
                        crash = make_pair(x, y-1);
                        break;
                    }
                    cart_positions[i] = make_pair(x, y-1);
                    cart_map[x][y-1] = '<';
                }
            }
            else if(map[x][y] == '|'){
                if (cart_map[x][y] == '^')
                {
                    if (cart_map[x - 1][y] != '.')
                    {
                        crash = make_pair(x - 1, y);
                        break;
                    }
                    cart_positions[i] = make_pair(x - 1, y);
                    cart_map[x - 1][y] = '^';
                }
                else if (cart_map[x][y] == 'v')
                {
                    if (cart_map[x + 1][y] != '.')
                    {
                        crash = make_pair(x+ 1, y);
                        break;
                    }
                    cart_positions[i] = make_pair(x + 1, y);
                    cart_map[x + 1][y] = 'v';
                }
            }
            cart_map[x][y] = '.';
        }
        if (crash.first != -1)
            break;
    }

    cout << "Crash Position: " << crash.first << " " << crash.second << endl;

    system("pause");

    return 0;
}