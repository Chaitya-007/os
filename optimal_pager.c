#include <stdio.h> 

int main()
{
    // Declare variables to store flags, loop counters, positions, maximum value, and page faults
    int flag1, flag2, flag3, i, j, k, position, max, faults = 0;
    // Define the number of frames in the memory
    int num_frames = 3;
    
    // Declare arrays to store frames and temporary values
    int frames[num_frames];
    int temp[num_frames];
    
    // Define the sequence of pages in the input stream
    int inputStream[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    // Calculate the number of pages in the input stream
    int num_pages = sizeof(inputStream) / sizeof(inputStream[0]);

    // Initialize all frames to -1, indicating they are empty
    for(i = 0; i < num_frames; i++){
        frames[i] = -1;
    }

    // Iterate through each page in the input stream
    for(i = 0; i < num_pages; i++){
        
        flag1 = flag2 = 0;

        // Check if the page is already in one of the frames (HIT)
        for(j = 0; j < num_frames; j++){
            if(frames[j] == inputStream[i]){
                   flag1 = flag2 = 1;
                   break;
               }
        }

        // If the page is not present in any frame (MISS)
        if(flag1 == 0){
            // Check if there is an empty frame to insert the page
            for(j = 0; j < num_frames; j++){
                if(frames[j] == -1){
                    faults++; // Increment the page fault count
                    frames[j] = inputStream[i]; // Insert the page into the empty frame
                    flag2 = 1;
                    break;
                }
            }    
        }

        // If there are no empty frames available
        if(flag2 == 0){
            flag3 = 0;

            // Iterate through each frame to find the position of the page that will be replaced
            for(j = 0; j < num_frames; j++){
                temp[j] = -1;

                // Search for the occurrence of each frame item in the future of the input stream
                for(k = i + 1; k < num_pages; k++){
                    if(frames[j] == inputStream[k]){
                        temp[j] = k; // Store the position of the page's next occurrence
                        break;
                    }
                }
            }

            // Determine the position of the page with the furthest future occurrence (Least Recently Used)
            for(j = 0; j < num_frames; j++){
                if(temp[j] == -1){
                    position = j; // If a frame item is not found in the future, choose it for replacement
                    flag3 = 1;
                    break;
                }
            }

            // If all frame items occur in the future, choose the one with the furthest occurrence
            if(flag3 == 0){
                max = temp[0];
                position = 0;

                for(j = 1; j < num_frames; j++){
                    if(temp[j] > max){
                        max = temp[j];
                        position = j;
                    }
                }               
            }

            // Replace the page in the chosen position with the current input page
            frames[position] = inputStream[i];
            faults++; // Increment the page fault count
        }

        printf("\n");
        
        // Print the current state of the frames after each page access
        for(j = 0; j < num_frames; j++){
            printf("%d\t", frames[j]);
        }
    }

    // Print the total number of page faults and hits
    printf("\n\nTotal Page Faults = %d", faults);
    printf("\nTotal Hits = %d", num_pages-faults);

    return 0;
}
