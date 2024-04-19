#include <iostream>
#include <vector>

using namespace std;

const int MAX_PROCESSES = 10; // Maximum number of processes
const int MAX_RESOURCES = 10; // Maximum number of resources

// Arrays to store the available, maximum allocation, current allocation, and need for each process
int available[MAX_RESOURCES];
int max_alloc[MAX_PROCESSES][MAX_RESOURCES];
int current_alloc[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

// Array to track whether a process has finished or not
bool finish[MAX_PROCESSES];

// Vector to store the safe sequence of processes
vector<int> safe_sequence;

// Function to check if the system is in a safe state
bool isSafe(int processes, int resources)
{
    // Initialize finish array to false for all processes
    for (int i = 0; i < processes; ++i)
    {
        finish[i] = false;
    }

    // Calculate the need matrix
    for (int i = 0; i < processes; ++i)
    {
        for (int j = 0; j < resources; ++j)
        {
            need[i][j] = max_alloc[i][j] - current_alloc[i][j];
        }
    }

    // Initialize work array to available resources
    int work[MAX_RESOURCES];
    for (int i = 0; i < resources; ++i)
    {
        work[i] = available[i];
    }

    int count = 0;
    // Loop until all processes are finished
    while (count < processes)
    {
        bool found = false;
        // Iterate through all processes
        for (int i = 0; i < processes; ++i)
        {
            // Check if the process is not finished
            if (!finish[i])
            {
                bool canBeProcessed = true;
                // Check if the process can be processed with the available resources
                for (int j = 0; j < resources; ++j)
                {
                    if (need[i][j] > work[j])
                    {
                        canBeProcessed = false;
                        break;
                    }
                }

                if (canBeProcessed)
                {
                    // If the process can be processed, update work array and finish the process
                    for (int j = 0; j < resources; ++j)
                    {
                        work[j] += current_alloc[i][j];
                    }
                    safe_sequence.push_back(i); // Add the process to the safe sequence
                    finish[i] = true; // Mark the process as finished
                    ++count; // Increment the count of finished processes
                    found = true;
                }
            }
        }
        // If no process can be processed, return false (unsafe state)
        if (!found)
        {
            return false;
        }
    }
    // If all processes are finished, return true (safe state)
    return true;
}

// Main function
int main()
{
    int processes, resources;

    // Input the number of processes and resources
    cout << "Enter the number of processes: ";
    cin >> processes;

    cout << "Enter the number of resources: ";
    cin >> resources;

    // Input the available instances of each resource
    cout << "Enter the available instances of each resource:\n";
    for (int i = 0; i < resources; ++i)
    {
        cin >> available[i];
    }

    // Input the maximum demand of each process
    cout << "Enter the maximum demand of each process:\n";
    for (int i = 0; i < processes; ++i)
    {
        cout << "For process " << i << ": ";
        for (int j = 0; j < resources; ++j)
        {
            cin >> max_alloc[i][j];
        }
    }

    // Input the current allocation of each process
    cout << "Enter the current allocation of each process:\n";
    for (int i = 0; i < processes; ++i)
    {
        cout << "For process " << i << ": ";
        for (int j = 0; j < resources; ++j)
        {
            cin >> current_alloc[i][j];
        }
    }

    // Check if the system is in a safe state
    if (isSafe(processes, resources))
    {
        // If safe, print the safe sequence
        cout << "System is in a safe state.\n";
        cout << "Safe sequence is: ";
        for (int i = 0; i < processes; ++i)
        {
            cout << safe_sequence[i] << " ";
        }
        cout << endl;
    }
    else
    {
        // If unsafe, print a message
        cout << "System is in an unsafe state.\n";
    }

    return 0;
}
