#include<stdio.h>
#include<limits.h>

// Function to check if incoming page is already present in the queue (HIT)
int checkHit(int incomingPage, int queue[], int occupied){
    
    // Iterate through the queue
    for(int i = 0; i < occupied; i++){
        // If incoming page matches with a page in the queue, return 1 (HIT)
        if(incomingPage == queue[i])
            return 1;
    }
    // If incoming page is not found in the queue, return 0 (MISS)
    return 0;
}

// Function to print the current state of the frame
void printFrame(int queue[], int occupied)
{
    // Iterate through the queue and print each element
    for(int i = 0; i < occupied; i++)
        printf("%d\t\t\t",queue[i]);
}

int main()
{
    // Array representing the incoming page stream
    int incomingStream[] = {1, 2, 3, 2, 1, 5, 2, 1, 6, 2, 5, 6, 3, 1, 3};
    
    // Calculate the number of elements in the incoming stream
    int n = sizeof(incomingStream)/sizeof(incomingStream[0]);
    // Number of frames in the memory
    int frames = 3;
    // Array to store the frame
    int queue[n];
    // Array to store the distance of each frame item from the current page in the stream (for LRU)
    int distance[n];
    // Variable to keep track of the number of occupied frames
    int occupied = 0;
    // Variable to count the number of page faults
    int pagefault = 0;
    
    // Print the headers for the output
    printf("Page\t\t Frame1 \t\t Frame2 \t\t Frame3\n");
    
    // Iterate through the incoming page stream
    for(int i = 0;i < n; i++)
    {
        // Print the current incoming page
        printf("%d:  \t\t",incomingStream[i]);
        
        // Check if the incoming page is already present in the frame (HIT)
        if(checkHit(incomingStream[i], queue, occupied)){
            // If HIT, print the current frame
            printFrame(queue, occupied);
        }
        // If the incoming page is not present in the frame (MISS)
        else if(occupied < frames){
            // If there are empty frames, add the incoming page to an empty frame
            queue[occupied] = incomingStream[i];
            // Increment the count of occupied frames
            occupied++;
            // Increment the page fault count
            pagefault++;
            // Print the current frame
            printFrame(queue, occupied);
        }
        else{
            // If all frames are occupied, find the least recently used (LRU) page to replace
            
            // Initialize the maximum distance to a minimum value
            int max = INT_MIN;
            int index;
            
            // Calculate the distance of each frame item from the current page in the stream
            for (int j = 0; j < frames; j++)
            {
                // Initialize the distance for each frame
                distance[j] = 0;
                
                // Traverse the incoming stream in reverse to find the distance of each frame item
                for(int k = i - 1; k >= 0; k--)
                {
                    // Increment the distance
                    ++distance[j];
                    
                    // If the frame item is found in the stream, break the loop
                    if(queue[j] == incomingStream[k])
                        break;
                }
                
                // Update the maximum distance and the index of the frame item with maximum distance
                if(distance[j] > max){
                    max = distance[j];
                    index = j;
                }
            }
            
            // Replace the frame item with the maximum distance (LRU) with the current incoming page
            queue[index] = incomingStream[i];
            // Print the current frame
            printFrame(queue, occupied);
            // Increment the page fault count
            pagefault++;
        }
        
        // Print a newline character to separate each page's output
        printf("\n");
    }
    
    // Print the total number of page faults
    printf("Page Fault: %d",pagefault);
    
    return 0;
}
