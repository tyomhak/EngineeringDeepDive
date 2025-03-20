#pragma once

#include <iostream>

struct ct_empty_node
{};

template<int Head, typename LNode = ct_empty_node, typename RNode = ct_empty_node>
struct ct_node
{
    static constexpr int value = Head;
    typedef LNode l;
    typedef RNode r;
};


// insert
template<typename Node, int Value>
struct insert_node;

template<typename Node, int Value, bool ToLeft>
struct insert_node_helper
{
    // default impl, assumes we're adding to left sub-tree
    typedef ct_node<Node::value, 
        typename insert_node<typename Node::l, Value>::type, 
        typename Node::r> type;
};

template<typename Node, int Value>
struct insert_node_helper<Node, Value, false>
{
    typedef ct_node<Node::value,
        typename Node::l,
        typename insert_node<typename Node::r, Value>::type> type;
};

template<typename Node, int Value>
struct insert_node
{
    typedef typename insert_node_helper<Node, Value, (Node::value > Value)>::type type;
};

template<int Value>
struct insert_node<ct_empty_node, Value>
{
    typedef ct_node<Value> type;
};


// find
template<bool chooseFirst, typename FirstType, typename SecondType>
struct TypeSelector
{
    typedef FirstType type;
};
template<typename FirstType, typename SecondType>
struct TypeSelector<true, FirstType, SecondType>
{
    typedef FirstType type;
};
template<typename FirstType, typename SecondType>
struct TypeSelector<false, FirstType, SecondType>
{
    typedef SecondType type;
};

template<typename Node, int Value>
struct find_node
{
    typedef typename TypeSelector<Value < Node::value, typename Node::l, typename Node::r>::type childNode;
    typedef typename find_node<childNode, Value>::type type;
};

template<int Value>
struct find_node<ct_empty_node, Value>
{
    static_assert(false, "Node not found");
};

template<typename Node>
struct find_node<Node, Node::value>
{
    typedef Node type;
};


// min
template<typename Node>
struct min_value
{
    static constexpr int inner_min = min_value<typename Node::l>::value;
    static constexpr int value = Node::value < inner_min ? Node::value : inner_min;
};

template<>
struct min_value<ct_empty_node>
{
    static constexpr int value = std::numeric_limits<int>::max();
};

// max
template<typename Node>
struct max_value
{
    static constexpr int inner_max = max_value<typename Node::r>::value;
    static constexpr int value = Node::value > inner_max ? Node::value : inner_max;
};

template<>
struct max_value<ct_empty_node>
{
    static constexpr int value = std::numeric_limits<int>::min();
};


// print
template<typename Node>
struct node_printer
{
    static void print()
    {
        std::cout << Node::value << ", ";
        node_printer<typename Node::l>::print();
        node_printer<typename Node::r>::print();
    }
};

template<>
struct node_printer<ct_empty_node>
{
    static void print()
    {
        std::cout << std::endl;
    }
};