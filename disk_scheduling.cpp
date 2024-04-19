#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Function to calculate total head movement for FIFO algorithm
int FIFO(int req[],int n,int head){
    int primary_movement = abs(req[0] - head); // Calculate head movement to the first request
    int total = 0;
    for(int i=0;i<n-1;i++){
       total += abs(req[i]-req[i+1]); // Calculate total head movement between consecutive requests
    }  
    return primary_movement + total; // Return total head movement
}

// Function to calculate total head movement for SSTF algorithm
int SSTF(int req[], int n, int head) {
    int total = 0;
    vector<int> requests(req, req + n); // Convert array to vector for easier manipulation
    vector<bool> visited(n, false); // Track whether a request has been visited

    for (int i = 0; i < n; ++i) {
        int temp = 9999999; // Initialize temporary variable to a large value
        int ci = -1; // Initialize index of closest request
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && abs(head - requests[j]) < temp) {
                temp = abs(head - requests[j]); // Calculate distance between head and request
                ci = j; // Update index of closest request
            }
        }
        visited[ci] = true; // Mark request as visited
        total += temp; // Add distance to total head movement
        head = requests[ci]; // Move head to closest request
    }
    return total; // Return total head movement
}

// Function to calculate total head movement for SCAN algorithm
int SCAN(int req[],int n,int md,int head,int dir){
    int ans = 0;
    if(dir==0){ // Direction is right
      int a = abs(md-head); // Distance to the end of the disk
      int minval = 999999;
      for(int i=0;i<n;i++){
        if(req[i]<minval){
            minval = req[i]; // Find the smallest request
        }
      }
      int b = abs(md-minval); // Distance from smallest request to the end of the disk
      int c = a+b; // Total head movement
      ans = c;
    }
    else if(dir==1){ // Direction is left
        int a = abs(head); // Distance to the beginning of the disk
        int maxval = 0;
        for(int i=0;i<n;i++){
        if(req[i]>maxval){
            maxval = req[i]; // Find the largest request
        }
        }
        int b = abs(maxval); // Distance from largest request to the beginning of the disk
        int c = a+b; // Total head movement
        ans = c;
    }
    return ans; // Return total head movement
}

// Function to calculate total head movement for C-SCAN algorithm
int CSCAN(int req[],int n,int md,int head,int dir){
    int ans = 0;
    //right direction
    if(dir==0){ // Direction is right
        int temp = 0;
        for(int i=0;i<n;i++){
            if(req[i]<head && req[i]>temp){
                temp = req[i]; // Find the largest request less than head position
            }
        }
        int a = abs(head-md); // Distance to the end of the disk
        int c = a + md + temp; // Total head movement
        ans = c;
    }
    //left direction
    else if(dir==1){ // Direction is left
        int temp = 999999;
        for(int i=0;i<n;i++){
            if(req[i]>head && req[i]<temp){
                temp = req[i]; // Find the smallest request greater than head position
            }
        }
        int c = head + md + temp; // Total head movement
        ans = c; 
    }
    return ans; // Return total head movement
}

// Main function
int main() {
    // Initialize request parameters
    int r_size = 7;
    int requests[] = {82,170,43,140,24,16,190};
    int requests2[] = {176, 79, 34, 60, 92, 11, 41, 114};
    int head = 50;
    int max_diskSize = 199; 

    // Print total head movement for each disk scheduling algorithm
    cout << "FIFO: " << FIFO(requests,r_size, head) << endl;
    cout << "SSTF: " << SSTF(requests,r_size, head) << endl;
    // 0 means right, 1 means left
    cout << "SCAN: " << SCAN(requests,r_size,max_diskSize,head,0) << endl;
    cout << "SCAN: " << SCAN(requests2,r_size,max_diskSize,head,1) << endl;
    cout << "C-SCAN: " << CSCAN(requests,r_size,max_diskSize,head,0) << endl;
    cout << "C-SCAN: " << CSCAN(requests2,r_size,max_diskSize,head,0) << endl;
    return 0;
}
