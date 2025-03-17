#include <iostream>
#include <string>
#include <vector>


#define TEST_VALUE_0 0
#define TEST_VALUE_1 1


class test_class
{
public:
    template<uint param>
    const char* get_info()
    { 
        static_assert(false, "Missing param type"); 
        return nullptr; 
    }

    
};

template<>
const char* test_class::get_info<TEST_VALUE_0>()
{
    return "0";
};

template<>
const char* test_class::get_info<TEST_VALUE_1>()
{
    return "1";
}


template<typename T>
struct add_ptr
{
    typedef T* type;
};

template<typename T>
struct remove_extent
{
    typedef T type;
};

template<typename T, size_t size>
struct remove_extent<T[size]>
{
    typedef T type;
};


template<typename T>
struct decay
{
    typedef T type;
};

template<typename T>
struct decay<const T>
{
    typedef typename decay<T>::type type;
};

template<typename T>
struct decay<T&>
{
    typedef typename decay<T>::type type;
};

template<typename T>
struct decay<T*>
{
    typedef typename decay<T>::type type;
};


template<typename T>
struct type_name_printer
{
    static std::string name() { return "NO INFO"; }
};

template<>
struct type_name_printer<float>
{
    static std::string name() { return "float"; }
};
template<>
struct type_name_printer<int>
{
    static std::string name() { return "int"; }
};

template<typename T, size_t size>
struct type_name_printer<T[size]>
{
    static std::string name()
    {
        return type_name_printer<T>::name() + "[" + std::to_string(size) + "]";
    }
};

template<typename T>
struct type_name_printer<T&>
{
    static std::string name()
    {
        return type_name_printer<T>::name() + "&";
    }
};

template<typename T>
struct type_name_printer<T*>
{
    static std::string name()
    {
        return type_name_printer<T>::name() + "*";
    }
};

template<typename T>
struct type_name_printer<const T>
{
    static std::string name()
    {
        return std::string("const ") + type_name_printer<T>::name();
    }
};

template<typename T>
struct type_name_printer<T* const>
{
    static std::string name()
    {
        return type_name_printer<T>::name() + "* " + std::string("const ");
    }
};

template<typename T>
struct type_name_printer<std::vector<T>>
{
    static std::string name()
    {
        return std::string("vector<") + type_name_printer<T>::name() + ">";
    }
};

int main()
{
    using std::cout;
    using std::endl;

    cout << std::is_same<add_ptr<int>::type, int*>::value << endl;

    cout << std::is_same<std::remove_extent<int>::type, int>::value << endl;
    cout << std::is_same<std::remove_extent<int[10]>::type, int>::value << endl;
    cout << std::is_same<std::remove_extent<int[10][5]>::type, int[5]>::value << endl;

    cout << std::is_same<decay<int*>::type, int>::value << endl;;
    cout << std::is_same<decay<const int* const>::type, int>::value << endl;
    cout << std::is_same<decay<const int* const>::type, double>::value << endl;


    cout << type_name_printer<int[15]>::name() << endl;
    cout << type_name_printer<const int*[15]>::name() << endl;
    cout << type_name_printer<float&>::name() << endl;
    cout << type_name_printer<std::vector<int>>::name() << endl;
    cout << type_name_printer<std::vector<const int* const *const ** const *>>::name() << endl;

    test_class temp{};
    cout << temp.get_info<TEST_VALUE_0>() << endl;
    cout << temp.get_info<TEST_VALUE_1>() << endl;
}