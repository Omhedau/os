#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> calculateRemainingNeed(vector<vector<int>> &maxNeed, vector<vector<int>> &allocated)
{
    int processes = maxNeed.size();
    int resources = maxNeed[0].size();

    vector<vector<int>> remainingNeed(processes, vector<int>(resources));

    for (int i = 0; i < processes; i++)
    {
        for (int j = 0; j < resources; j++)
        {
            remainingNeed[i][j] = maxNeed[i][j] - allocated[i][j];
        }
    }
    return remainingNeed;
}

bool isSafe(int processes, int resources, vector<vector<int>> &remainingNeed,
            vector<int> &
                available,
            vector<vector<int>> &allocated)
{
    vector<int> work = available;
    vector<bool> finish(processes, false);
    vector<int> safeSequence;
    for (int k = 0; k < processes; ++k)
    {
        for (int i = 0; i < processes; ++i)
        {
            if (!finish[i])
            {
                bool canAllocate = true;
                for (int j = 0; j < resources; ++j)
                {
                    if (remainingNeed[i][j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate)
                {
                    for (int j = 0; j < resources; ++j)
                    {
                        work[j] += allocated[i][j];
                    }
                    safeSequence.push_back(i);
                    finish[i] = true;
                }
            }
        }
    }
    if (safeSequence.size() == processes)
    {
        cout << "Safe Sequence is : ";
        for (int i = 0; i < processes; ++i)
        {
            cout << "P" << safeSequence[i];
            if (i != processes - 1)
                cout << " -> ";
        }
        cout << endl;
        return true;
    }
    else
    {
        cout << "Deadlock will occur!" << endl;
        return false;
    }
}

int main()
{
    int processes, resources;
    cout << "Enter the number of processes ";
    cin >> processes;
    cout << "Enter the number of Resources ";
    cin >> resources;

    vector<vector<int>> maxNeed(processes, vector<int>(resources));

    cout << "enter the max need of each processes " << endl;

    for (int i = 0; i < processes; i++)
    {
        cout << "p" << i << " ";
        for (int j = 0; j < resources; j++)
        {
            cin >> maxNeed[i][j];
        }
    }

    vector<vector<int>> allocated(processes, vector<int>(resources));

    cout << "Enter the allocated resources to processes " << endl;
    for (int i = 0; i < processes; i++)
    {
        cout << "p" << i << " ";
        for (int j = 0; j < resources; j++)
        {
            cin >> allocated[i][j];
        }
    }

    vector<int> totalResources(resources);

    cout << "Enter the total num of Resources ";
    for (int i = 0; i < resources; i++)
    {
        cin >> totalResources[i];
    }

    vector<int> available(resources);

    for (int i = 0; i < resources; i++)
    {
        int total = totalResources[i];
        for (int j = 0; j < processes; j++)
        {
            total -= allocated[j][i];
        }
        available[i] = total;
    }

    vector<vector<int>> remainingNeed = calculateRemainingNeed(maxNeed, allocated);

    cout << "Remaining need of each process " << endl;
    for (int i = 0; i < processes; i++)
    {
        cout << "p" << i << " ";
        for (int j = 0; j < resources; j++)
        {
            cout << remainingNeed[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Available resources ";

    for (int i = 0; i < resources; i++)
    {
        cout << available[i] << " ";
    }

    cout << endl;

    isSafe(processes, resources, remainingNeed, available, allocated);

    return 0;
}