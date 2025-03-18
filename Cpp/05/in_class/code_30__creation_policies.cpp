
// Let's observe other use-case of template template arguments.
// 
// At first we declare set of objects:

struct CircularObject {};
struct RectangularObject {};
struct LinearObject {};
struct ConeObject {};


// Next, there are several creational strategies:

template< typename ObjectType >
struct SequentialBuilder {};

template< typename ObjectType >
struct ParallelBuilder {};

template< typename ObjectType >
struct PostponedBuilder {};


// Next, we want to compare pairs of strategies.
//
// Note, we want to COMPARE THE BUILDERS themselves, and not their various 
// instantiations.


template< 
		template< typename T > class Builder1, 
		template< typename T > class Builder2 >
struct BuildersComparator
{
	/// Compares provided 2 Builders on circular objects.
	void compareOnCircles() const {
		Builder1< CircularObject > b1;
		Builder2< CircularObject > b2;
		//
		// compare 'b1' and 'b2' ...
	}

	/// Compares provided 2 Builders on rectangular objects.
	void compareOnRectangles() const {
		Builder1< RectangularObject > b1;
		Builder2< RectangularObject > b2;
		//
		// compare 'b1' and 'b2' ...
	}

	/// Compares provided 2 Builders on cone objects.
	void compareOnCones() const {
		Builder1< ConeObject > b1;
		Builder2< ConeObject > b2;
		//
		// compare 'b1' and 'b2' ...
	}

	/// Performs overall comparison of the 2 provided Builders.
	void compare() const {
		if ( ... )  //  <-- compare depending on some condition
			compareOnCircles();
		if ( ... )
			compareOnRectangles();
		if ( ... )
			compareOnCones();
	}
};


// In the 'main()' function below, we COMARE DIFFERENT PAIRS of builders...
//
// Note, this results in:
//  * comparing different pairs of builds,
//  * each of them on different sets of object types.
//
// So the performed functionality is kind of QUADRATIC, while the code stays LINEAR.


int main()
{
	BuildersComparator< SequentialBuilder, ParallelBuilder > cmp1;
	cmp1.compare();

	BuildersComparator< ParallelBuilder, PostponedBuilder > cmp2;
	cmp2.compare();

	BuildersComparator< PostponedBuilder, SequentialBuilder > cmp3;
	cmp3.compare();

	return 0;
}


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
