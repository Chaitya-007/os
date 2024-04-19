#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Define a structure for memory blocks
struct MemoryBlock
{
    int id;           // Identifier for the memory block
    int size;         // Size of the memory block
    bool allocated;   // Indicates whether the memory block is allocated or not
};

// Function to allocate memory using First Fit technique
void firstFit(vector<MemoryBlock> &memory, int blockSize, int id)
{
    // Iterate through each memory block
    for (int i = 0; i < memory.size(); ++i)
    {
        // Check if the block is not allocated and has sufficient size
        if (!memory[i].allocated && memory[i].size >= blockSize)
        {
            // Allocate the memory block
            memory[i].allocated = true;
            memory[i].id = id;
            // Print the allocation details
            cout << "Memory block " << id << " allocated at position " << i << endl;
            return;
        }
    }
    // If no suitable block is found, print failure message
    cout << "Memory block " << id << " cannot be allocated." << endl;
}

// Function to allocate memory using Best Fit technique
void bestFit(vector<MemoryBlock> &memory, int blockSize, int id)
{
    int bestFitIndex = -1;
    int minFragmentation = INT_MAX;
    // Iterate through each memory block
    for (int i = 0; i < memory.size(); ++i)
    {
        // Check if the block is not allocated and has sufficient size
        if (!memory[i].allocated && memory[i].size >= blockSize)
        {
            int fragmentation = memory[i].size - blockSize;
            // Update best fit if current block has less fragmentation
            if (fragmentation < minFragmentation)
            {
                minFragmentation = fragmentation;
                bestFitIndex = i;
            }
        }
    }
    // If a suitable block is found, allocate it
    if (bestFitIndex != -1)
    {
        memory[bestFitIndex].allocated = true;
        memory[bestFitIndex].id = id;
        cout << "Memory block " << id << " allocated at position " << bestFitIndex << endl;
    }
    else
    {
        cout << "Memory block " << id << " cannot be allocated." << endl;
    }
}

// Function to allocate memory using Next Fit technique
void nextFit(vector<MemoryBlock> &memory, int blockSize, int id, int &nextFitIndex)
{
    // Iterate through memory blocks starting from the last allocation index
    for (int i = nextFitIndex; i < memory.size(); ++i)
    {
        // Check if the block is not allocated and has sufficient size
        if (!memory[i].allocated && memory[i].size >= blockSize)
        {
            // Allocate the memory block
            memory[i].allocated = true;
            memory[i].id = id;
            // Print the allocation details
            cout << "Memory block " << id << " allocated at position " << i << endl;
            nextFitIndex = i + 1; // Update nextFitIndex for next allocation
            return;
        }
    }
    // Wrap around if not found from nextFitIndex to end
    for (int i = 0; i < nextFitIndex; ++i)
    {
        // Check if the block is not allocated and has sufficient size
        if (!memory[i].allocated && memory[i].size >= blockSize)
        {
            // Allocate the memory block
            memory[i].allocated = true;
            memory[i].id = id;
            // Print the allocation details
            cout << "Memory block " << id << " allocated at position " << i << endl;
            nextFitIndex = i + 1; // Update nextFitIndex for next allocation
            return;
        }
    }
    // If no suitable block is found, print failure message
    cout << "Memory block " << id << " cannot be allocated." << endl;
}

// Function to allocate memory using Worst Fit technique
void worstFit(vector<MemoryBlock> &memory, int blockSize, int id)
{
    int worstFitIndex = -1;
    int maxFragmentation = INT_MIN;
    // Iterate through each memory block
    for (int i = 0; i < memory.size(); ++i)
    {
        // Check if the block is not allocated and has sufficient size
        if (!memory[i].allocated && memory[i].size >= blockSize)
        {
            int fragmentation = memory[i].size - blockSize;
            // Update worst fit if current block has more fragmentation
            if (fragmentation > maxFragmentation)
            {
                maxFragmentation = fragmentation;
                worstFitIndex = i;
            }
        }
    }
    // If a suitable block is found, allocate it
    if (worstFitIndex != -1)
    {
        memory[worstFitIndex].allocated = true;
        memory[worstFitIndex].id = id;
        cout << "Memory block " << id << " allocated at position " << worstFitIndex << endl;
    }
    else
    {
        cout << "Memory block " << id << " cannot be allocated." << endl;
    }
}

// Main function
int main()
{
    // Declare variables for memory size and block size
    int memorySize, blockSize;
    // Prompt user to enter memory size
    cout << "Enter total memory size: ";
    cin >> memorySize;
    // Prompt user to enter number of memory blocks
    cout << "Enter number of memory blocks: ";
    int numBlocks;
    cin >> numBlocks;
    // Create a vector to store memory blocks
    vector<MemoryBlock> memory(numBlocks);
    // Prompt user to enter size of each memory block
    for (int i = 0; i < numBlocks; ++i)
    {
        cout << "Enter size of block " << i + 1 << ": ";
        cin >> memory[i].size;
        memory[i].allocated = false;
    }

    int choice;
    // Menu-driven loop for memory allocation techniques
    do
    {
        cout << "\nMemory Allocation Techniques:\n";
        cout << "1. First Fit\n";
        cout << "2. Best Fit\n";
        cout << "3. Next Fit\n";
        cout << "4. Worst Fit\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter size of block to allocate: ";
            cin >> blockSize;
            firstFit(memory, blockSize, choice);
            break;
        case 2:
            cout << "Enter size of block to allocate: ";
            cin >> blockSize;
            bestFit(memory, blockSize, choice);
            break;
        case 3:
            cout << "Enter size of block to allocate: ";
            cin >> blockSize;
            nextFit(memory, blockSize, choice, choice);
            break;
        case 4:
            cout << "Enter size of block to allocate: ";
            cin >> blockSize;
            worstFit(memory, blockSize, choice);
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
