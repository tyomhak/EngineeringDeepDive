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