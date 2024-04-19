#include<iostream> // Include the input-output stream header file

using namespace std; // Use the standard namespace

int main(){ // Main function

  int n; // Declare variable to store the number of processes
  cout<<"Enter the number of processes : "; // Output prompt to enter the number of processes
  cin>>n; // Read the number of processes from the user

  int process[n]; // Declare an array to store process IDs
  int priority[n]; // Declare an array to store priorities
  int burst[n]; // Declare an array to store burst times
  int arrival[n]; // Declare an array to store arrival times

  // Input priorities for processes
  cout<<"Enter the priority for processes : "; // Output prompt to enter priorities
  for(int i=0;i<n;i++){ // Loop to input priorities for each process
     int x; // Declare variable to store priority
     cin>>x; // Read priority from the user
     process[i] = i+1; // Assign process ID (starts from 1)
     priority[i] = x; // Store priority in the array
  }

  // Input arrival times for processes
  cout<<"Enter the arrival time for processes : "; // Output prompt to enter arrival times
  for(int i=0;i<n;i++){ // Loop to input arrival times for each process
     int y; // Declare variable to store arrival time
     cin>>y; // Read arrival time from the user
     arrival[i] = y; // Store arrival time in the array
  }

  // Input burst times for processes
  cout<<"Enter the burst time for processes : "; // Output prompt to enter burst times
  for(int i=0;i<n;i++){ // Loop to input burst times for each process
     int y; // Declare variable to store burst time
     cin>>y; // Read burst time from the user
     burst[i] = y; // Store burst time in the array
  }

  // Sort the processes based on priority (and arrival time for processes with the same priority)
  for(int i = 0; i < n; i++) { // Outer loop for selection sort
      int pos = i; // Initialize position of minimum priority
      for(int j = i + 1; j < n; j++) { // Inner loop to find minimum priority
          if(priority[j] < priority[pos] || (priority[j] == priority[pos] && arrival[j] < arrival[pos])) {
              pos = j; // Update position of minimum priority
          }
      }

      // Swap priority
      int temp = priority[i];
      priority[i] = priority[pos];
      priority[pos] = temp;

      // Swap burst time
      temp = burst[i];
      burst[i] = burst[pos];
      burst[pos] = temp;

      // Swap process ID
      temp = process[i];
      process[i] = process[pos];
      process[pos] = temp;

      // Swap arrival time
      temp = arrival[i];
      arrival[i] = arrival[pos];
      arrival[pos] = temp;
  }

  int wt[n]; // Declare an array to store waiting times
  int tt[n]; // Declare an array to store turnaround times
  wt[0] = 0; // Initialize waiting time for the first process to 0
  for(int i=1;i<n;i++){ // Loop to calculate waiting times for other processes
     wt[i] = burst[i-1] + wt[i-1]; // Waiting time = burst time of previous process + waiting time of previous process
  }
  for(int i=0;i<n;i++){ // Loop to calculate turnaround times for all processes
     tt[i] = wt[i] + burst[i]; // Turnaround time = waiting time + burst time
  }

  // Calculate total waiting time and total turnaround time
  float totalwt = 0; // Variable to store total waiting time
  for(int i=0;i<n;i++){ // Loop to sum up waiting times
    totalwt += wt[i]; // Add each waiting time to the total
  }
  float totaltt = 0; // Variable to store total turnaround time
  for(int i=0;i<n;i++){ // Loop to sum up turnaround times
    totaltt += tt[i]; // Add each turnaround time to the total
  }

  // Output process details
  cout<<"Process id"<<"\t"<<"Arrival Time"<<"\t"<<"Priority"<<"\t"<<"Burst Time"<<"\t"<<"Waiting Time"<<"\t"<<"Turnaround Time"<<endl;
  for(int i=0;i<n;i++){ // Loop to display process details
    cout<<process[i]<<"\t\t"<<arrival[i]<<"\t\t"<<priority[i]<<"\t\t"<<burst[i]<<"\t\t"<<wt[i]<<"\t\t"<<tt[i]<<endl;
  }

  // Output average waiting time and average turnaround time
  cout<<"Average Waiting time for process is : "; // Output prompt for average waiting time
  float avgwt = totalwt/n; // Calculate average waiting time
  cout<<avgwt; // Output average waiting time
  cout<<"\n";
  cout<<"Average Turnaround time for process is : "; // Output prompt for average turnaround time
  float avgtt = totaltt/n; // Calculate average turnaround time
  cout<<avgtt; // Output average turnaround time
  cout<<"\n";
  return 0; // Return 0 to indicate successful execution
}
