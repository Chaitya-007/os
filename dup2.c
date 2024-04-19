#include <fcntl.h>     // Header file for file control options
#include <stdio.h>     // Standard I/O functions
#include <sys/types.h> // Header file for system data types
#include <sys/wait.h>  // Header file for wait functions
#include <unistd.h>    // Header file for POSIX operating system API

int main() {
  int fd[2], pid; // Declare file descriptors and process ID

  // Open file "file1.txt" for reading only and get the file descriptor
  int filedes = open("file1.txt", O_RDONLY);

  // Redirect standard input (stdin) to the file descriptor
  dup2(filedes, fileno(stdin));

  // Close the file descriptor since it's no longer needed
  close(filedes);

  // Create a pipe with file descriptors fd[0] for reading and fd[1] for writing
  pipe(fd);

  // Fork a child process
  if ((pid = fork()) == 0) { // Child process
    // Redirect standard output (stdout) to the write end of the pipe
    dup2(fd[1], fileno(stdout));

    // Close the read end of the pipe since it's not needed in this process
    close(fd[0]);

    // Close the write end of the pipe since it's not needed in this process
    close(fd[1]);

    // Replace the current process image with the "sort" command
    execl("/usr/bin/sort", "sort", (char *)0);
  } else if (pid > 0) { // Parent process
    // Redirect standard input (stdin) to the read end of the pipe
    dup2(fd[0], fileno(stdin));

    // Close the write end of the pipe since it's not needed in this process
    close(fd[1]);

    // Close the read end of the pipe since it's not needed in this process
    close(fd[0]);

    // Replace the current process image with the "uniq" command
    execl("/usr/bin/uniq", "uniq", (char *)0);
  } else { // Fork failed
    perror("fork"); // Print an error message
    exit(1);        // Exit the program with an error status
  }

  return 0; // Exit the program with success status
}
