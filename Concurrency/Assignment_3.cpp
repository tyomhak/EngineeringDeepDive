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
        status = execl("/bin/echo", "echo", "Hello from the child process", NULL);
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(&status);
        std::cout << "Parent process done" << std::endl;
    }

    return 0;
}