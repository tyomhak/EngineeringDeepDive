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