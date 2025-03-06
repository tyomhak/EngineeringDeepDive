#include <iostream>
#include <vector>
#include <string>
#include <utility>

/*
Write a function template, which will print content of provided `std::vector<>` to the console. 
If it is vector of integers, an example output is:
	[5, 32, 14, 6]
*/
template<typename T>
void print_vec(const std::vector<T>& vec)
{
    std::cout << "[";
    if (!vec.empty())
    {
        for (auto i = 0; i < vec.size() - 1; ++i)
            std::cout << vec.at(i) << ", ";
        std::cout << vec.back();
    }
    std::cout << "]" << std::endl;
}

/*
Write its specialization for printing vector of strings, so every string will be double-quoted. 
Example output is:
	["hello", "kitty", "move", "on"]
*/
template<typename T>
void print_vec_enclosed(const std::vector<T>& vec, const std::string& prefix, const std::string& postfix)
{
    std::cout << "[";
    if (!vec.empty())
    {
        for (auto i = 0; i < vec.size() - 1; ++i)
            std::cout << prefix << vec.at(i) << postfix << ", ";
        std::cout << prefix << vec.back() << postfix;
    }
    std::cout << "]" << std::endl;
}

template<>
void print_vec(const std::vector<std::string>& vec)
{
    print_vec_enclosed(vec, "\"", "\"");
}

/*
Write another specialization for printing vector of characters, which will print every character in single quotes. 
Example:
	['f', 'h', 'Z', 'X']
*/
template<>
void print_vec(const std::vector<char>& vec)
{
    print_vec_enclosed(vec, "\'", "\'");
}


/*
Write a specialization for printing vector of `std::pair<>` objects. 
In that case, each pair should appear in brackets. 
If the vector consists of pairs of strings and integers, then example output is:
	[(h:22), (ptr:7), (key:84)]
*/
template<typename T, typename U>
void print_vec(const std::vector<std::pair<T, U>>& vec)
{
    std::cout << "[";
    if (!vec.empty())
    {
        for (auto i = 0; i < vec.size() - 1; ++i)
        {
            const auto& [first, second] = vec.at(i);
            std::cout << "(" << first << ":" << second << "), "; 
        }
        const auto& [first, second] = vec.back();
        std::cout << "(" << first << ":" << second << ")"; 
    }
    std::cout << "]" << std::endl;
}



int main()
{
    std::vector<int> v_empty{};
    print_vec(v_empty);

    std::vector<int> vi{1,2,3,4,5};
    print_vec(vi);

    std::vector<std::string> vs{"hello", "world", "!"};
    print_vec(vs);

    std::vector<char> vc{'h', 'e', 'l', 'l', 'o'};
    print_vec(vc);

    std::vector<std::pair<std::string, int>> vp {
        {"hello", 0},
        {"world", 1},
        {"!", 2}
    };
    print_vec(vp);
}