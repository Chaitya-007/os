#include<iostream>  // Header file for input/output stream
#include<vector>    // Header file for vectors
using namespace std;

int main(){
  int n;  // Declare variable to store the number of processes
  cout<<"Enter the number of processes : ";  // Prompt user to enter the number of processes
  cin>>n;  // Read the number of processes entered by the user

  int process[n];   // Array to store process IDs
  int arrival[n];   // Array to store arrival times of processes
  int burst[n];     // Array to store burst times of processes

  cout<<"Enter the arrival time for processes : ";  // Prompt user to enter arrival times of processes
  for(int i=0;i<n;i++){   // Loop to input arrival times for each process
     int x;
     cin>>x;   // Read arrival time for the current process
     process[i] = i+1;   // Assign process ID (starting from 1)
     arrival[i] = x;     // Store arrival time in the array
  }

  cout<<"Enter the burst time for processes : ";  // Prompt user to enter burst times of processes
  for(int i=0;i<n;i++){   // Loop to input burst times for each process
     int y;
     cin>>y;   // Read burst time for the current process
     burst[i] = y;   // Store burst time in the array
  }

  // Sort the processes based on arrival time
  for(int i=0;i<n;i++){
    int pos = i;
    for(int j=i+1;j<n;j++){
        // Find the position of the smallest arrival time
        if(arrival[j]<arrival[pos])
            pos = j;
     }

     // Swap arrival time
     int temp;
     temp = arrival[i];
     arrival[i] = arrival[pos];
     arrival[pos] = temp;

     // Swap burst time
     int temp1;
     temp1 = burst[i];
     burst[i] = burst[pos];
     burst[pos] = temp1;

     // Swap process ID
     int temp2;
     temp2 = process[i];
     process[i] = process[pos];
     process[pos] = temp2;
  }

  int wt[n];    // Array to store waiting times of processes
  int tt[n];    // Array to store turnaround times of processes
  vector<int> ct(n, 0);   // Vector to store completion times of processes, initialized with size n and all elements as 0
  ct[-1] = 0;   // Set completion time of the first process to 0

  // Calculate completion times of processes
  for(int i=0;i<n;i++){
    ct[i] = ct[i-1] + burst[i];   // Completion time of the current process = completion time of previous process + burst time of current process
  }

  // Calculate turnaround times of processes
  for(int i=0;i<n;i++){
    tt[i] = ct[i] - arrival[i];   // Turnaround time = Completion time - Arrival time
  }

  // Calculate waiting times of processes
  for(int i=0;i<n;i++){
    wt[i] = tt[i] - burst[i];   // Waiting time = Turnaround time - Burst time
  }

  // Calculate total completion time of all processes
  float totalct = 0;
  for(int i=0;i<n;i++){
    totalct += ct[i];
  }

  // Calculate total turnaround time of all processes
  float totaltt = 0;
  for(int i=0;i<n;i++){
    totaltt += tt[i];
  }

  // Calculate total waiting time of all processes
  float totalwt = 0;
  for(int i=0;i<n;i++){
    totalwt += wt[i];
  }

  // Output the process details table
  cout<<"Process id"<<"\t"<<"Arrival Time"<<"\t"<<"Burst Time"<<"\t"<<"Completion Time"<<"\t"<<"Turnaround Time"<<"\t"<<"Waiting Time"<<endl;
  for(int i=0;i<n;i++){
    cout<<process[i]<<"\t\t"<<arrival[i]<<"\t\t"<<burst[i]<<"\t\t"<<ct[i]<<"\t\t"<<tt[i]<<"\t\t"<<wt[i]<<endl;
  }

  // Output total completion time
  cout<<"Total Completion time for process is : ";
  cout<<totalct;
  cout<<" milliseconds\n";

  // Output average waiting time
  cout<<"Average Waiting time for process is : ";
  float avgwt = totalwt/n;
  cout<<avgwt;
  cout<<"\n";

  // Output average turnaround time
  cout<<"Average Turnaround time for process is : ";
  float avgtt = totaltt/n;
  cout<<avgtt;
  cout<<"\n";

  return 0;   // Exit the program with success status
}
