#pragma once

#include <cstddef>


// #include <vector>


// template<typename T>
// class stack
// {
// public:
//     void push(const T& val) { return _data.push_back(val); }
//     void pop() { return _data.pop_back(); }

//     T& top() { return *_data.rbegin(); }
//     const T& top() const { return *_data.crbegin(); }

//     size_t size() const { return _data.size(); }
//     bool empty() const { return _data.empty(); }

// private:
//     std::vector<T> _data{};
// };


// template<>
// class stack<bool>
// {
// public:
//     void push(bool val) { return _data.push_back(val); }
//     void pop() { return _data.pop_back(); }

//     auto& top() { return _data.rbegin(); }
//     const auto& top() const { return *_data.crbegin(); }

//     size_t size() const { return _data.size(); }
//     bool empty() const { return _data.empty(); }


// private:
//     std::vector<bool> _data{};
// };




template<typename T, size_t max_size>
class stack
{
public:
    void push(const T& val) 
    { 
        _data[_size++] = val; 
    }

    void pop()
    {
        --_size;
    }

    T& top()
    { 
        return _data[_size - 1]; 
    }

    const T& top() const 
    { 
        return _data[_size - 1]; 
    }

    size_t size() const { return _size; }
    bool empty() const { return _size == 0; }

private:
    T _data[max_size];
    size_t _size = 0;
};




template<size_t max_size>
struct stackb_val
{
    stack<bool, max_size>* stack_ptr{nullptr};
    size_t ndx{0};

    operator bool()
    { 
        return stack_ptr->_get(ndx);
    }

    auto& operator=(bool val) 
    {
        stack_ptr->_set(ndx, val);
        return *this;
    }
};

template<size_t max_size>
class stack<bool, max_size>
{
public:
    void push(bool val) 
    {
        _set(_size++, val);
    }

    void pop()
    {
        _size--;
    }

    auto top() { return stackb_val<max_size>{this, _size - 1}; }
    const auto top() const { return _get(_size - 1); }

    size_t size() const { return _size; }
    bool empty() const { return _size == 0; }

private:
    bool _get(size_t ndx) {
        auto byteNdx = ndx / 8;
        auto bitNdx = ndx % 8;

        return _data[byteNdx] & (1 << bitNdx);
    }

    void _set(size_t ndx, bool val)
    {
        auto byteNdx = ndx / 8;
        auto bitNdx = ndx % 8;

        if (val)
            _data[byteNdx] = _data[byteNdx] | (1 << bitNdx);
        else
            _data[byteNdx] = _data[byteNdx] & ~(1 << bitNdx);
    }

    

private:
    unsigned char _data[max_size / 8 + (max_size % 8 ? 1 : 0)];
    size_t _size = 0;

    friend stackb_val<max_size>;
};