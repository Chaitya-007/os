#include<iostream> // Include the input-output stream library
using namespace std; // Using the standard namespace

int main(){
  int n; // Declare variable for the number of processes
  cout<<"Enter the number of processes : "; // Prompt user to enter the number of processes
  cin>>n; // Read the number of processes from user input

  int process[n]; // Declare an array to store process IDs
  int arrival[n]; // Declare an array to store arrival times
  int burst[n]; // Declare an array to store burst times

  cout<<"Enter the arrival time for processes : "; // Prompt user to enter arrival times for each process
  for(int i=0;i<n;i++){ // Loop to read arrival times
     int x;
     cin>>x; // Read arrival time from user input
     process[i] = i+1; // Assign process IDs
     arrival[i] = x; // Store arrival time in the array
  }
  cout<<"Enter the burst time for processes : "; // Prompt user to enter burst times for each process
  for(int i=0;i<n;i++){ // Loop to read burst times
     int y;
     cin>>y; // Read burst time from user input
     burst[i] = y; // Store burst time in the array
  }

  // Sort the processes based on burst time (Shortest Job First)
  for(int i=0;i<n;i++){ // Outer loop for each process
    int pos = i; // Initialize position variable
    for(int j=i+1;j<n;j++){ // Inner loop to find position of minimum burst time
       if(burst[j]<burst[pos]) // Compare burst times
           pos = j; // Update position if a smaller element is found
    }

    // Swap burst time
    int temp;
    temp = burst[i];
    burst[i] = burst[pos];
    burst[pos] = temp;

    // Swap arrival time
    temp = arrival[i];
    arrival[i] = arrival[pos];
    arrival[pos] = temp;

    // Swap process IDs
    temp = process[i];
    process[i] = process[pos];
    process[pos] = temp;
  }

  int wt[n]; // Declare an array to store waiting times
  int tt[n]; // Declare an array to store turnaround times
  wt[0] = 0; // Set waiting time for the first process to 0
  for(int i=1;i<n;i++){ // Loop to calculate waiting times for subsequent processes
     wt[i] = burst[i-1] + wt[i-1]; // Waiting time = Burst time of previous process + Waiting time of previous process
  }
  for(int i=0;i<n;i++){ // Loop to calculate turnaround times for each process
     tt[i] = wt[i] + burst[i]; // Turnaround Time = Waiting Time + Burst Time
  }

  float totalwt = 0; // Initialize variable to store total waiting time
  for(int i=0;i<n;i++){ // Loop to calculate total waiting time
    totalwt += wt[i]; // Accumulate waiting times
  }
  float totaltt = 0; // Initialize variable to store total turnaround time
  for(int i=0;i<n;i++){ // Loop to calculate total turnaround time
    totaltt += tt[i]; // Accumulate turnaround times
  }

  // Print process details
  cout<<"Process id"<<"\t"<<"Arrival Time"<<"\t"<<"Burst Time"<<"\t"<<"Waiting Time"<<"\t"<<"Turnaround Time"<<endl;
  for(int i=0;i<n;i++){ // Loop to print details of each process
    cout<<process[i]<<"\t\t"<<arrival[i]<<"\t\t"<<burst[i]<<"\t\t"<<wt[i]<<"\t\t"<<tt[i]<<endl;
  }

  // Print average waiting time
  cout<<"Average Waiting time for process is : ";
  float avgwt = totalwt/n; // Calculate average waiting time
  cout<<avgwt<<"\n";

  // Print average turnaround time
  cout<<"Average Turnaround time for process is : ";
  float avgtt = totaltt/n; // Calculate average turnaround time
  cout<<avgtt<<"\n";

  return 0; // Exit the program
}
