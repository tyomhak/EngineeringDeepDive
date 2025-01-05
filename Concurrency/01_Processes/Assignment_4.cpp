// Fork and Exec with Command-Line Arguments
// Objective: Use fork and execl to run a command with multiple arguments.

// Prepare a test.txt file with some text.
// Write a program that:
// Uses fork to create a child process.
// The child process should use execl to run the grep command to search for a specific word (e.g., "main") in a text file (e.g., test.txt).
// The parent process should print "Parent process completed".
// Expected Output: The lines in the file test.txt that contain the word "main" followed by "Parent process completed".

#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main()
{
    int status;
    pid_t pid = fork();
    if (pid == -1)
        return 1;
    else if (pid == 0)
    {
        status = execl("/bin/grep", "grep", "main", "./text.txt", NULL);
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(&status);
        std::cout << "Parent process completed" << std::endl;
    }

    return 0;
}