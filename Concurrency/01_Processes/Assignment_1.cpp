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