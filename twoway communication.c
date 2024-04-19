#include <stdio.h> // Include standard input-output library
#include <unistd.h> // Include functions related to system calls

int main() // Main function
{
   int pipefds1[2], pipefds2[2]; // Declare two pipes, each with read and write file descriptors
   int returnstatus1, returnstatus2; // Variables to store the return status of pipe creation
   int pid; // Variable to store process ID
   char pipe1writemessage[20] = "Hi"; // Message to be written to pipe 1
   char pipe2writemessage[20] = "Hello"; // Message to be written to pipe 2
   char readmessage[20]; // Buffer to store read message

   returnstatus1 = pipe(pipefds1); // Create pipe 1 and store return status

   if (returnstatus1 == -1) // Check if pipe creation failed
   {
      printf("Unable to create pipe 1 \n"); // Display error message
      return 1; // Return error code
   }
   returnstatus2 = pipe(pipefds2); // Create pipe 2 and store return status

   if (returnstatus2 == -1) // Check if pipe creation failed
   {
      printf("Unable to create pipe 2 \n"); // Display error message
      return 1; // Return error code
   }
   pid = fork(); // Fork a new process

   if (pid != 0) // Parent process
   {
      close(pipefds1[0]); // Close the read side of pipe 1 in parent
      close(pipefds2[1]); // Close the write side of pipe 2 in parent
      printf("In Parent: Writing to pipe 1 – Message is %s\n", pipe1writemessage); // Display message being written to pipe 1
      write(pipefds1[1], pipe1writemessage, sizeof(pipe1writemessage)); // Write message to pipe 1
      read(pipefds2[0], readmessage, sizeof(readmessage)); // Read message from pipe 2
      printf("In Parent: Reading from pipe 2 – Message is %s\n", readmessage); // Display message read from pipe 2
   }
   else // Child process
   {                      
      close(pipefds1[1]); // Close the write side of pipe 1 in child
      close(pipefds2[0]); // Close the read side of pipe 2 in child
      read(pipefds1[0], readmessage, sizeof(readmessage)); // Read message from pipe 1
      printf("In Child: Reading from pipe 1 – Message is %s\n", readmessage); // Display message read from pipe 1
      printf("In Child: Writing to pipe 2 – Message is %s\n", pipe2writemessage); // Display message being written to pipe 2
      write(pipefds2[1], pipe2writemessage, sizeof(pipe2writemessage)); // Write message to pipe 2
   }
   return 0; // Return 0 to indicate successful execution
}
