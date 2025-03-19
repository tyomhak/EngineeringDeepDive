#pragma once

#include "../in_class/code_50__ct_multitype_sequence.hpp"

// Exercises:

// 1) Implement removal of all the values which are of given type 'T'.
template<typename Seq, typename T>
struct ct_remove_t
{
    typedef ct_multitype_sequence<typename Seq::head_type, Seq::head, 
        typename ct_remove_t<typename Seq::body_type, T>::type> type;
};

template<typename Seq>
struct ct_remove_t<Seq, typename Seq::head_type>
{
    typedef typename Seq::body_type inner_type;
    typedef typename ct_remove_t<inner_type, typename Seq::head_type>::type type;
};

template<typename T>
struct ct_remove_t<ct_empty_sequence, T>
{
    typedef ct_empty_sequence type;
};

// 2) Implement filtering of all those values, which are of given type 'T'.
template<typename Seq, typename T>
struct ct_filter_t
{
    typedef typename ct_filter_t<typename Seq::body_type, T>::type type;
};

template<typename Seq>
struct ct_filter_t<Seq, typename Seq::head_type>
{
    typedef ct_multitype_sequence<typename Seq::head_type, Seq::head,
        typename ct_filter_t<typename Seq::body_type, typename Seq::head_type>::type> type;
};

template<typename T>
struct ct_filter_t<ct_empty_sequence, T>
{
    typedef ct_empty_sequence type;
};