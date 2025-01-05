// Multiple Forks and Execs
// Objective: Work with multiple child processes created using fork and run different commands using execl.

// Write a program that:
// Creates two child processes using fork.
// The first child process should use execl to run the ls command.
// The second child process should use execl to run the date command.
// The parent process should print "Parent process done" after creating both child processes.
// Expected Output: The output of the ls command followed by the output of the date command, and finally the parent's message.


#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

bool call_ls()
{
    int status;
    pid_t pid = fork();
    if (pid == -1)
        return false;
    else if (pid == 0)
    {
        status = execl("/bin/ls", "ls", NULL);
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(&status);
    }

    return true;
}

bool call_date()
{
    int status;
    pid_t pid = fork();
    if (pid == -1)
        return false;
    else if (pid == 0)
    {
        status = execl("/bin/date", "date", NULL);
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(&status);
    }

    return true;
}

int main()
{
    call_ls();
    call_date();
    std::cout << "Parent process done" << std::endl;
}