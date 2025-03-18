#pragma once

// Exercise:
//
// 1) Assume we have:
//       * collection of receivers,
//       * collection of transformers,
//       * collection of senders.
//    A Combiner works on one receiver, one transformer and one sender.
//    Write a logger (function or class) for behavior of provided Combiner. Logger must 
//       instantiate the Combiner with certain tripples of {receiver, transformer, sender}.
//

struct Receiver1{};
struct Receiver2{};
struct Receiver3{};
struct Receiver4{};

struct Transformer1{};
struct Transformer2{};
struct Transformer3{};
struct Transformer4{};

struct Sender1{};
struct Sender2{};
struct Sender3{};
struct Sender4{};

template<typename RecT, typename TransT, typename SendT>
struct SimpleCombiner
{
    SimpleCombiner(const RecT& r, const TransT& t, const SendT& s)
    {};
};

template<typename RecT, typename TransT, typename SendT>
struct ComplexCombiner
{
    ComplexCombiner(const RecT& r, const TransT& t, const SendT& s)
    {};
};

template<
    template<typename R, typename T, typename S> class Combiner,
    typename RT, typename TT, typename ST>
struct Logger
{
    Combiner<RT, TT, ST> combiner{RT(), TT(), ST()};
};

