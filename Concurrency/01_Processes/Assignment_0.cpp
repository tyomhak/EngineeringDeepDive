// Multiple Fork calls
// Objective: Understand the process hierarchy when multiple sequential fork syscalls are invoked.

// Write a program that:
// Calls multiple  fork syscalls one after another. Check what the process tree looks like.
// Pay attention to the hierarchy of processes, how many parents and children are created


#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


bool print_proc_tree() 
{
    int status;
    pid_t pstree_pid = fork();
    if (pstree_pid == -1)
        return false;
    else if (pstree_pid == 0)
    {
        int status;
        status = execl("/bin/pstree", "pstree", NULL);
        if (status == -1) 
        {
            std::cerr << "Failed to call pstree" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        pstree_pid = wait(&status);
        return WIFEXITED(status);
    }

    return true;
}

bool new_fork(int& curr_proc_num)
{
    pid_t pid;
    pid = fork();
    if (pid == -1)
    {
        std::cerr << "Failed to fork" << std::endl;
        return false;
    }
    if (pid == 0)
    {
        ++curr_proc_num;
        pid_t ppid = getppid();
        std::cout << "Child (" << std::to_string(getpid()) << "), from parent (" << std::to_string(ppid) << ")" << std::endl;
    }
    else
    {
        pid_t curr_pid = getpid();
        std::cout << "I (" << std::to_string(curr_pid) << ") forked " << std::to_string(pid) << std::endl;
    }

    return true;
}

int main()
{
    int proc_number = 0;

    for (int i = 0; i < 3; ++i)
    {
        if (new_fork(proc_number) && proc_number == 0)
        { 
            print_proc_tree();
        }
    }

    return 0;
}