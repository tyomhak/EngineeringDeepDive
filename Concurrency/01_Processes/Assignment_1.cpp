// Simple Fork and Exec
// Objective: Understand the creation of a child process using fork and how to replace it with a new program using execl.

// Write a program that:
// Uses fork to create a child process.
// In the child process, use execl to run the ls command to list the contents of the current directory.
// The parent process should print "Parent process done" after the child process is created.
// Expected Output: The directory listing should be printed, followed by the parent's message.



#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1) 
    {
        std::cerr << "Failed fork" << std::endl;
        return -1;
    } 
    else if (pid == 0) 
    {
        status = execl("/bin/ls", "ls", NULL);
        if (status == -1)
        {
            std::cerr << "Failed execl" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        pid_t finished_process_pid;
        do {
            finished_process_pid = wait(&status);
        } 
        while (finished_process_pid != pid);

        std::cout << "Parent process done" << std::endl;
    }
}