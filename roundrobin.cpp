#include <iostream> // Include the input-output stream library
#include <vector> // Include the vector library for dynamic arrays
using namespace std; // Using the standard namespace

int main() {
    int n, tq; // Declare variables for the number of processes and time quantum
    cout << "Enter the number of processes : "; // Prompt user to enter the number of processes
    cin >> n; // Read the number of processes from user input
    int process[n]; // Declare an array to store process IDs
    int arrival[n]; // Declare an array to store arrival times
    int burst[n]; // Declare an array to store burst times
    vector<int> ct(n); // Declare a vector to store completion times

    cout << "Enter the arrival time for processes : "; // Prompt user to enter arrival times for each process
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x; // Read arrival time from user input
        process[i] = i + 1; // Assign process IDs
        arrival[i] = x; // Store arrival time in the array
    }

    cout << "Enter the burst time for processes : "; // Prompt user to enter burst times for each process
    for (int i = 0; i < n; i++) {
        int y;
        cin >> y; // Read burst time from user input
        burst[i] = y; // Store burst time in the array
    }

    cout << "Enter the time quantum : "; // Prompt user to enter the time quantum for Round Robin scheduling
    cin >> tq; // Read the time quantum from user input

    // Sort the processes based on arrival time
    for(int i = 0; i < n; i++) {
        int pos = i;
        for(int j = i + 1; j < n; j++) {
            if(arrival[j] < arrival[pos])
                pos = j;
        }

        // Swap arrival time
        int temp = arrival[i];
        arrival[i] = arrival[pos];
        arrival[pos] = temp;

        // Swap burst time
        temp = burst[i];
        burst[i] = burst[pos];
        burst[pos] = temp;

        // Swap process IDs
        temp = process[i];
        process[i] = process[pos];
        process[pos] = temp;
    }

    // Round Robin scheduling
    int wt[n] = {0}; // Declare an array to store waiting times
    int tt[n] = {0}; // Declare an array to store turnaround times
    int inc = 0; // Initialize a variable to track time
    int remaining[n]; // Declare an array to store remaining burst times for each process
    for (int i = 0; i < n; i++)
        remaining[i] = burst[i]; // Initialize remaining burst times

    // Perform Round Robin scheduling
    while (true) {
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                done = false;
                if (remaining[i] > tq) {
                    inc += tq;
                    remaining[i] -= tq;
                } else {
                    inc = inc + remaining[i];
                    remaining[i] = 0;
                    ct[i] = inc; // Update completion time for the process
                }
            }
        }
        if (done == true)
            break;
    }

    // Calculate turnaround time and waiting time for each process
    for(int i = 0; i < n; i++) {
        tt[i] = ct[i] - arrival[i]; // Turnaround time = Completion time - Arrival time
        wt[i] = tt[i] - burst[i]; // Waiting time = Turnaround time - Burst time
    }

    // Calculate total completion time, turnaround time, and waiting time
    float totalct = 0;
    for(int i = 0; i < n; i++) {
        totalct += ct[i];
    }
    float totaltt = 0;
    for(int i = 0; i < n; i++) {
        totaltt += tt[i];
    }
    float totalwt = 0;
    for(int i = 0; i < n; i++) {
        totalwt += wt[i];
    }

    // Print process details
    cout << "Process id\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << process[i] << "\t\t" << arrival[i] << "\t\t" << burst[i] << "\t\t" << ct[i] << "\t\t" << tt[i] << "\t\t" << wt[i] << endl;
    }

    // Print total completion time, average waiting time, and average turnaround time
    cout << "Total Completion time for process is : ";
    cout << totalct << " milliseconds\n";
    cout << "Average Waiting time for process is : ";
    float avgwt = totalwt / n;
    cout << avgwt << "\n";
    cout << "Average Turnaround time for process is : ";
    float avgtt = totaltt / n;
    cout << avgtt << "\n";

    return 0; // Exit the program
}
