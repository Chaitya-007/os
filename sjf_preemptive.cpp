#include<iostream> // Include the input-output stream library
using namespace std; // Using the standard namespace

// Function to calculate waiting time for each process
void findWaitingTime(int process[], int arrival[], int burst[], int wt[], int n) {  
   int rt[n]; // Declare an array to store remaining burst time for each process
   for (int i = 0; i < n; i++)  
      rt[i] = burst[i]; // Initialize remaining burst time

   int complete = 0, t = 0, minm = 9876543; // Initialize variables for completion, time, and minimum
   int shortest = 0, finish_time; // Initialize variables for shortest process and finish time
   bool check = false; // Initialize a boolean variable to check if a process is chosen

   // Loop until all processes are completed
   while (complete != n) {  
      // Find the process with the shortest remaining time and ready to execute
      for (int j = 0; j < n; j++) {  
         if ((arrival[j] <= t) && (rt[j] < minm) && rt[j] > 0) {  
            minm = rt[j]; // Update minimum remaining time
            shortest = j; // Update shortest process index
            check = true; // Set check flag to true
         }  
      }  

      // If no process is ready to execute, increment time and continue
      if (check == false) {  
         t++;  
         continue;  
      }  

      // Decrement the remaining time of the chosen process
      rt[shortest]--;  
      minm = rt[shortest];  

      // If the process is completed, update completion time and waiting time
      if (minm == 0) {  
         complete++; // Increment the number of completed processes
         check = false; // Reset check flag
         finish_time = t + 1; // Update finish time
         
         // Calculate waiting time
         wt[shortest] = finish_time - burst[shortest] - arrival[shortest];  
         if (wt[shortest] < 0)  
            wt[shortest] = 0; // Ensure waiting time is non-negative
      }  

      // Increment time
      t++;  
   }  
}

int main(){
  int n; // Declare variable for the number of processes
  cout << "Enter the number of processes : "; // Prompt user to enter the number of processes
  cin >> n; // Read the number of processes from user input

  int process[n]; // Declare an array to store process IDs
  int arrival[n]; // Declare an array to store arrival times
  int burst[n]; // Declare an array to store burst times

  cout << "Enter the arrival time for processes : "; // Prompt user to enter arrival times for each process
  for(int i = 0; i < n; i++){ // Loop to read arrival times
     int x;
     cin >> x; // Read arrival time from user input
     process[i] = i + 1; // Assign process IDs
     arrival[i] = x; // Store arrival time in the array
  }

  cout << "Enter the burst time for processes : "; // Prompt user to enter burst times for each process
  for(int i = 0; i < n; i++){ // Loop to read burst times
     int y;
     cin >> y; // Read burst time from user input
     burst[i] = y; // Store burst time in the array
  }

  // Sort the processes based on arrival time
  for(int i = 0; i < n; i++){ // Outer loop for each process
    int pos = i; // Initialize position variable
    for(int j = i + 1; j < n; j++){ // Inner loop to find position of minimum element
        if(arrival[j] < arrival[pos]) // Compare arrival times
            pos = j; // Update position if a smaller element is found
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

  int wt[n]; // Declare an array to store waiting times
  int tt[n]; // Declare an array to store turnaround times

  // Call the function to calculate waiting times
  findWaitingTime(process, arrival, burst, wt, n);  

  // Calculate turnaround time
  for(int i = 0; i < n; i++){ // Loop to calculate turnaround time for each process
     tt[i] = wt[i] + burst[i]; // Turnaround Time = Waiting Time + Burst Time
  }

  float totalwt = 0; // Initialize variable to store total waiting time
  for(int i = 0; i < n; i++){ // Loop to calculate total waiting time
    totalwt += wt[i]; // Accumulate waiting times
  }

  float totaltt = 0; // Initialize variable to store total turnaround time
  for(int i = 0; i < n; i++){ // Loop to calculate total turnaround time
    totaltt += tt[i]; // Accumulate turnaround times
  }

  // Print process details
  cout << "Process id" << "\t" << "Arrival Time" << "\t" << "Burst Time" << "\t" << "Waiting Time" << "\t" << "Turnaround Time" << endl;
  for(int i = 0; i < n; i++){ // Loop to print details of each process
    cout << process[i] << "\t\t" << arrival[i] << "\t\t" << burst[i] << "\t\t" << wt[i] << "\t\t" << tt[i] << endl;
  }

  // Print average waiting time
  cout << "Average Waiting time for process is : ";
  float avgwt = totalwt / n; // Calculate average waiting time
  cout << avgwt << "\n";

  // Print average turnaround time
  cout << "Average Turnaround time for process is : ";
  float avgtt = totaltt / n; // Calculate average turnaround time
  cout << avgtt << "\n";

  return 0; // Exit the program
}
