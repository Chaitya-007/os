// C program for FIFO page replacement algorithm
#include <stdio.h>

int main()
{
    // Define the incoming stream of page requests
    int incomingStream[] = {4, 1, 2, 4, 5};
    // Initialize the number of page faults to 0
    int pageFaults = 0;
    // Define the number of frames in the memory
    int frames = 3;
    // Declare variables for iteration and tracking
    int m, n, s, pages;

    // Calculate the number of pages in the incoming stream
    pages = sizeof(incomingStream) / sizeof(incomingStream[0]);

    // Print the header for the output table
    printf("Incoming \t\t\t Frame 1 \t\t\t Frame 2 \t\t\t Frame 3");
    
    // Initialize an array to store the frames with -1 (indicating empty)
    int temp[frames];
    for (m = 0; m < frames; m++)
    {
        temp[m] = -1;
    }

    // Iterate through each page in the incoming stream
    for (m = 0; m < pages; m++)
    {
        // Initialize variable to track whether the page is already in a frame
        s = 0;

        // Check if the current page is already in a frame
        for (n = 0; n < frames; n++)
        {
            if (incomingStream[m] == temp[n])
            {
                // If the page is found, increment the counter and decrement page faults
                s++;
                pageFaults--;
            }
        }
        // Increment page faults since the page is not found in any frame
        pageFaults++;

        // If there are empty frames or the page is not already in a frame
        if ((pageFaults <= frames) && (s == 0))
        {
            // Put the current page in an empty frame
            temp[m] = incomingStream[m];
        }
        // If there are no empty frames and the page is not already in a frame
        else if (s == 0)
        {
            // Replace the oldest page in a frame with the current page
            temp[(pageFaults - 1) % frames] = incomingStream[m];
        }

        // Print the incoming page and the frames after each page request
        printf("\n");
        printf("%d\t\t\t", incomingStream[m]);
        for (n = 0; n < frames; n++)
        {
            // Print the content of each frame
            if (temp[n] != -1)
                printf(" %d\t\t\t", temp[n]);
            else
                printf(" - \t\t\t");
        }
    }

    // Print the total number of page faults
    printf("\nTotal Page Faults:\t%d\n", pageFaults);
    return 0;
}
