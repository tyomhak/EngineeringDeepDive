#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <vector>
#include <string>
#include <algorithm>
#include <optional>

struct command
{
    std::string path{};
    std::string file{};
    std::vector<std::string> args{};
};

std::optional<command> get_command(const std::string& user_input) 
{
    if (user_input.empty())
        return std::nullopt;

    auto space_it = std::find(user_input.begin(), user_input.end(), ' ');

    auto path = std::string(user_input.begin(), space_it);
    auto argv0 = path.substr(path.find_last_of("/") + 1);

    auto path_given = std::find(path.begin(), path.end(), '/') != path.end();
    if (!path_given)
        path = "/bin/" + path;

    command new_command{};
    new_command.path = path;
    new_command.file = argv0;

    while (space_it != user_input.end())
    {
        while (space_it != user_input.end() && *space_it == ' ')
            space_it++;
  
        if (space_it == user_input.end())
            break;

        auto next_space_it = std::find(space_it + 1, user_input.end(), ' ');
        new_command.args.push_back(std::string(space_it, next_space_it));
        space_it = next_space_it;
    }

    return new_command;
}

int run(const char* path, char* const* args)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        std::cerr << "Failed fork" << std::endl;
        return -1;
    }
    if (pid == 0)
    {
        int status = execv(path, args);
        if (status == -1)
        {
            std::cerr << "Failed execv" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        pid_t ended_proc_pid;
        int status;
        do {
            ended_proc_pid = wait(&status);
        }
        while (ended_proc_pid != pid);
    }
    return 0;
}


int main()
{
    std::string user_input{};
    while (std::getline(std::cin, user_input) && user_input != "exit")
    {
        if (auto opt_command = get_command(user_input); opt_command.has_value())
        {
            auto [path, argv0, args] = opt_command.value();
            std::vector<char*> args_array{};

            args_array.push_back(const_cast<char*>(argv0.c_str()));
            for (auto& arg : args)
                args_array.push_back(const_cast<char*>(arg.c_str()));
            args_array.push_back(NULL);

            run(path.c_str(), &args_array[0]);
        }
        else
            continue;
    }

    return 0;
}