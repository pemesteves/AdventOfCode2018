#include <iostream>
#include <thread>
#include <vector>
#include <utility>
#include <mutex>

using namespace std;

vector<vector<int>> total_power(300, vector<int>(300, 0));
vector<vector<int>> other_power(300, vector<int>(300, 0));
int serial_number;
pair<int, int> position;
int largest_power, size;
mutex mtx;

void calculate_total_power(int i, int j)
{
    int rackID = i + 10;
    int powerLevel = rackID * j;
    powerLevel += serial_number;
    powerLevel *= rackID;
    int digit = (powerLevel / 100) % 10;
    total_power[i][j] = digit - 5;
    mtx.lock();
    if (total_power[i][j] > largest_power)
    {
        largest_power = total_power[i][j];
        position = make_pair(i, j);
        size = 1;
    }
    mtx.unlock();
}

void calculate_largest_power(int i, int j, int grid_size)
{
    if(i + grid_size >= 300 || j + grid_size >= 300)
        return;

    int power = other_power[i][j];
    for (int k = i; k < i + grid_size - 1; k++)
    {
		power += total_power[k][j + grid_size - 1];
    }

	for (int k = j; k < j + grid_size - 1; k++)
	{
		power += total_power[i + grid_size - 1][k];
	}

	power += total_power[i + grid_size - 1][j + grid_size - 1];

    mtx.lock();
    if (power > largest_power)
    {
        position = make_pair(i, j);
        largest_power = power;
        size = grid_size;
    }
    mtx.unlock();

    other_power[i][j] = power;
}

int main()
{
    cin >> serial_number;
    vector<thread> threads;

    largest_power = 31;
    position = make_pair(21, 41);
    size = 3;

    for (int i = 0; i < 300; i++)
    {
        for (int j = 0; j < 300; j++)
        {
            threads.push_back(thread(calculate_total_power, i, j));
        }
    }

    for (int i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }

    threads.clear();
    other_power = total_power;

    for (int k = 2; k <= 300; k++)
    {
        for (int i = 0; i <= 300-k; i++)
        {
            for (int j = 0; j <= 300-k; j++)
            {
                threads.push_back(thread(calculate_largest_power, i, j, k));
            }
			for (int i = 0; i < threads.size(); i++)
				threads[i].join();
			threads.clear();
        }
    }

    cout << position.first << "x" << position.second << ": " << size << endl;
    system("pause");

    return 0;
}