#include <stdio.h> // Include standard input-output library
#include <string.h> // Include string manipulation library
#include <stdlib.h> // Include standard library
#include <sys/types.h> // Include data types used in system calls
#include <sys/wait.h> // Include wait-related functions for processes
#include <unistd.h> // Include functions related to system calls

int main(int argc, char **argv) // Main function with command line arguments
{
    int t = 1; // Variable to control the loop
    while (t == 1) // Loop until t is 1
    {
        printf("\nSystem Calls : "); // Display available system calls
        printf("\n1) Fork "); // Option 1: Fork
        printf("\n2) Copy(cp) "); // Option 2: Copy
        printf("\n3) Grep"); // Option 3: Grep
        printf("\n4) Exit "); // Option 4: Exit
        printf("\n**Select one option : "); // Prompt user to select an option
        int n; // Variable to store user input
        scanf("%d", &n); // Read user input

        switch (n) // Switch statement based on user input
        {
        case 1: // Option 1: Fork
        {
            pid_t pid; // Variable to store process ID
            int status; // Variable to store child process status
            pid = fork(); // Fork a new process
            if (pid == 0) // Child process
            {
                printf("=> Child\n"); // Display child process message
                printf("It is a child process and pid is %d.\n", getpid()); // Display child process ID
                execl("/bin/ls", "ls", "-l", "/home/pccoe/", (char *)0); // Execute ls command
                perror("In exec(): "); // Print error if execl fails
            }
            else if (pid > 0) // Parent process
            {
                printf("=> Parent\n"); // Display parent process message
                printf("I am a parent process and pid is %d.\n", getpid()); // Display parent process ID
                pid = wait(&status); // Wait for child process to finish
                printf("End of process %d: ", pid); // Display end of child process
                if (WIFEXITED(status)) // Check if child process terminated normally
                {
                    printf("The process ended with exit(%d).\n", WEXITSTATUS(status)); // Display exit status
                }
                if (WIFSIGNALED(status)) // Check if child process terminated due to signal
                {
                    printf("The process ended with kill -%d.\n", WTERMSIG(status)); // Display termination signal
                }
            }
            else // Error handling for fork failure
            {
                printf("ERROR"); // Display error message
                perror("In fork():"); // Print error message
            }
            break;
        }
        case 2: // Option 2: Copy
        {
            if (argc < 3) // Check if command line arguments are sufficient
            {
                printf("Insufficient arguments!\n"); // Display error message
                break;
            }
            if (strcmp(argv[1], argv[2]) != 0) // Check if source and destination files are different
            {
                char fs[100]; // Array to store file content
                FILE *fptr; // File pointer for source file
                fptr = fopen(argv[1], "r+"); // Open source file in read mode
                if (fptr) // Check if file opened successfully
                {
                    FILE *fn = fopen(argv[2], "w"); // Open destination file in write mode
                    while (fscanf(fptr, "%s", fs) != EOF) // Read content from source file
                    {
                        fprintf(fn, "%s\n", fs); // Write content to destination file
                    }
                    fclose(fn); // Close destination file
                }
                else // Error handling for file not found or failed to open
                {
                    printf("\nOops... File does not exist or failed to open..\n"); // Display error message
                }
                fclose(fptr); // Close source file
            }
            else // Error handling for same source and destination files
            {
                printf("\nSource and Destination files are same\n"); // Display error message
            }
            break;
        }
        case 3: // Option 3: Grep
        {
            if (argc < 4) // Check if command line arguments are sufficient
            {
                printf("Insufficient arguments!\n"); // Display error message
                break;
            }
            char fs[100]; // Array to store file content
            FILE *fptr; // File pointer for input file
            fptr = fopen(argv[3], "r+"); // Open input file in read mode
            if (fptr) // Check if file opened successfully
            {
                if (strcmp(argv[1], "-c") == 0) // Check if option is for counting occurrences
                {
                    int count = 0; // Variable to store occurrence count
                    while (fscanf(fptr, "%s", fs) != EOF) // Read content from file
                    {
                        if (strcmp(argv[2], fs) == 0) // Compare word with input argument
                        {
                            count++; // Increment count if word matches
                        }
                    }
                    printf("count = %d\n", count); // Display count of occurrences
                }
                fclose(fptr); // Close input file
            }
            else // Error handling for file not found or failed to open
            {
                printf("\nOops... File does not exist or failed to open...\n"); // Display error message
            }
            break;
        }
        case 4: // Option 4: Exit
            t = 0; // Set loop control variable to exit loop
            break;
        default: // Default case for invalid argument
            printf("Invalid argument!!"); // Display error message
        }
    }
    return 0; // Return 0 to indicate successful execution
}
