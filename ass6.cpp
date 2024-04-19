#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct memoryBlock
{
    int id;
    int size;
    bool allocated;
};

void firstFit(vector<memoryBlock> &memory, vector<int> &processes)
{
    for (int i = 0; i < processes.size(); i++)
    {
        for (int j = 0; j < memory.size(); j++)
        {
            if (!memory[j].allocated && memory[j].size >= processes[i])
            {
                memory[j].allocated = true;
                memory[j].id = i;
                break;
            }
        }
    }
}

void bestFit(vector<memoryBlock>& memory, vector<int>& processes) {
    for (int i = 0; i < processes.size(); ++i) {
        int bestIndex = -1;
        for (int j = 0; j < memory.size(); ++j) {
            if (!memory[j].allocated && memory[j].size >= processes[i]) {
                if (bestIndex == -1 || memory[j].size < memory[bestIndex].size) {
                    bestIndex = j;
                }
            }
        }
        if (bestIndex != -1) {
            memory[bestIndex].allocated = true;
            memory[bestIndex].id = i;
        }
    }
}

void nextFit(vector<memoryBlock>& memory, vector<int>& processes) {
    int lastAllocatedIndex = -1;
    for (int i = 0; i < processes.size(); ++i) {
        for (int j = (lastAllocatedIndex + 1) % memory.size(); j != lastAllocatedIndex; j = (j + 1) % memory.size()) {
            if (!memory[j].allocated && memory[j].size >= processes[i]) {
                memory[j].allocated = true;
                memory[j].id = i;
                lastAllocatedIndex = j;
                break;
            }
        }
    }
}

void worstFit(vector<memoryBlock>& memory, vector<int>& processes){
    for(int i=0;i<processes.size();i++){
        int worstIndex = -1;
        for(int j=0;j<memory.size();j++){
            if(!memory[j].allocated && memory[j].size >= processes[i]){
                if(worstIndex == -1 || memory[worstIndex].size < memory[j].size){
                    worstIndex = j;
                }
            }
        }
        if(worstIndex != -1){
            memory[worstIndex].allocated = true;
            memory[worstIndex].id = i;
        }
    }
}




int main()
{
    int numOfBlocks, numOfProcess;
    cout << "Enter the num of blocks ";
    cin >> numOfBlocks;
    cout << "Enter the num of process ";
    cin >> numOfProcess;

    vector<memoryBlock> memory(numOfBlocks);
    vector<int> processes(numOfProcess);

    cout << "Enter the size of the memory blocks " << endl;
    for (int i = 0; i < numOfBlocks; i++)
    {
        cout << i + 1 << " | :";
        cin >> memory[i].size;
        memory[i].allocated = false;
    }

    cout << "Enter size of the process" << endl;
    for (int i = 0; i < numOfProcess; i++)
    {
        cout << "p" << i + 1 << " | :";
        cin >> processes[i];
    }

    cout << "Memory Allocation using First Fit" << endl;
    firstFit(memory, processes);
    for (int i = 0; i < numOfBlocks; i++)
    {
        if (memory[i].allocated)
        {
            cout << "memory block " << i + 1 << " allocated to p" << memory[i].id + 1 << endl;
        }
        else
        {
            cout << "Memory Block " << i + 1 << " not allocated" << endl;
        }
    }
   
    for (auto& block : memory)
    block.allocated = false;

    
    cout << "\nMemory Allocation using Best Fit" << endl;
    bestFit(memory, processes);
    for (int i = 0; i < numOfBlocks; i++)
    {
        if (memory[i].allocated)
        {
            cout << "memory block " << i + 1 << " allocated to p" << memory[i].id + 1 << endl;
        }
        else
        {
            cout << "Memory Block " << i + 1 << " not allocated" << endl;
        }
    }
    
    for (auto& block : memory)
    block.allocated = false;
    
    cout << "\nMemory Allocation using Next Fit:\n";
    nextFit(memory, processes);
    for (int i = 0; i < numOfBlocks; ++i) {
        if (memory[i].allocated)
            cout << "Memory Block " << i + 1 << " allocated to P" << memory[i].id + 1 << endl;
        else
            cout << "Memory Block " << i + 1 << " not allocated\n";
    }
    
    for (auto& block : memory)
        block.allocated = false;

    cout << "\nMemory Allocation using Worst Fit:\n";
    worstFit(memory, processes);
    for (int i = 0; i < numOfBlocks; ++i) {
        if (memory[i].allocated)
            cout << "Memory Block " << i + 1 << " allocated to P" << memory[i].id + 1 << endl;
        else
            cout << "Memory Block " << i + 1 << " not allocated\n";
    }

    return 0;
}