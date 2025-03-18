

// At first, let's declare several different types of Workers.

struct NormalWorker {};
struct FastWorker {};
struct EconomWorker {};
struct LazyWorker {};
struct OptimalWorker {};


// Next come the methods of combining them into tasks.

/// A combiner, which arranges provided "Worker" classes sequentialy.
template< typename Worker1, typename Worker2, typename Worker3 >
struct SequentialCombiner {};

/// A combiner, which arranges provided "Worker" classes in parallel.
template< typename Worker1, typename Worker2, typename Worker3 >
struct ParallelCombiner {};

/// A combiner, which arranges provided "Worker" classes in a postponed way.
template< typename Worker1, typename Worker2, typename Worker3 >
struct PostponedCombiner {};


// Now, let's do some comparison of Combiners in an ordinary way

template< typename Combiner1, typename Combiner2 >
struct BasicComparator
{
	// Do some comparison here.
};


// Finally, let's do the comparison in template template argument way.

template< 
		template< typename W1, typename W2, typename W3 > class Combiner1, 
		template< typename W1, typename W2, typename W3 > class Combiner2, 
		typename Worker1, typename Worker2, typename Worker3 >
struct PromptComparator
{
	typedef Combiner1< Worker1, Worker2, Worker3 > Combiner1Type;
	typedef Combiner2< Worker1, Worker2, Worker3 > Combiner2Type;

	// Do the same comparison here.
};


int main()
{
	// Running comparators in a regular way
	{
		BasicComparator<
				SequentialCombiner< NormalWorker, EconomWorker, OptimalWorker >, 
				ParallelCombiner< NormalWorker, EconomWorker, OptimalWorker > > cmp1;
		//
		// run 'cmp1'.

		BasicComparator<
				ParallelCombiner< LazyWorker, EconomWorker, NormalWorker >,
				PostponedCombiner< LazyWorker, EconomWorker, NormalWorker > > cmp2;
		//
		// run 'cmp2'.

		// We see that the declarations ARE TOO TEDIOUS.
	}

	// Running comparators in the way of template-template arguments
	{
		PromptComparator<
				SequentialCombiner, 
				ParallelCombiner, 
				NormalWorker, EconomWorker, OptimalWorker > cmp1;
		//
		// run 'cmp1'.

		PromptComparator<
				ParallelCombiner, 
				PostponedCombiner, 
				LazyWorker, EconomWorker, NormalWorker > cmp2;
		//
		// run 'cmp2'.

		// The declarations here ARE MORE CONVENIENT.
		//
		// ... and LESS RISC of doing a typo, as there is no code duplication.
	}

	return 0;
}
