
// In previous versions of the language, there were cases when the same 
// function must be written for different amount of arguments.

float dot_product_1D( float x1, float x2 )
	{ return x1*x2; }

float dot_product_2D( float x1, float y1, float x2, float y2 )
	{ return x1*x2 + y1*y2; }

float dot_product_3D( float x1, float y1, float z1, float x2, float y2, float z2 )
	{ return x1*x2 + y1*y2 + z1*z2; }


// Same refers also to classes

template< typename T1, typename T2 >
struct group_2
	{ T1 _v1; T2 _v2; };

template< typename T1, typename T2, typename T3 >
struct group_3
	{ T1 _v1; T2 _v2; T3 _v3; };

template< typename T1, typename T2, typename T3, typename T4 >
struct group_4
	{ T1 _v1; T2 _v2; T3 _v3; T4 _v4; };


// We see here "kind of" repetition of code, which doesn't bring any new logic.
//
// Variadic templates were introduced to solve this.
// Let's observe the syntax:


template< typename... Types >  //   <-- Introduce sequence of types, called "Types"
struct group_variadic
{
	group_variadic( Types... args )  //   <-- Declare variables of those "Types"
	{
		// Some code here

		log( args... );  //   <-- Comma-separate all those variables
	}
};

// The analogy for 3-long list is:

template< typename Type0, typename Type1, typename Type2 >
struct group_ordinary
{
	group_ordinary( Type0 arg0_, Type1 arg1_, Type2 arg2_ )
	{
		// Some code here

		log( arg0_, arg1_, arg2_ );
	}
};


// The "..." operator is calles "ellipsis operator",
//
// And "args_" is called "parameters pack".


// Important point: ellipsis operator (...) doesn't introduce any new functionality,
//    ... nor imposes something on how the code should run.
// It just acts as a replacement of some lists, written directly in the code.


// Placement of ellipsis operator (...) is important. Let's observe few examples:


template< typename... Types >
void func( Types... args )
{
	g( args... );  //  -->  g( arg0, arg1, arg2, ... )

	h( args )...;  //  -->  h( arg0 ), h( arg1 ), h( arg2 ), ...

	Z( (u( args ) + v( args ))... );  //  -->  Z( u(arg0) + v(arg0) , u(arg1) + v(arg1) ,
	                                  //          u(arg2) + v(arg2) , ... )

	Z( u(args...) + v(args...) );  //  -->  Z( u( arg0, arg1, arg2, ... ) + v( arg0, arg1, arg2, ... ) )
}


// We see that "..." can be interpreted as:   VVV
//    
//    "repeat what it refers to".


// There is "sizeof..." operator, which returns number of items in the pack:

template< typename... Types >
void func_2( Types... args )
{
	cout << "The parameter pack is " << sizeof...(args) << "-long." << endl;
}

// This should not be confused with "sizeof", as the latter one returns 
// number of bytes.

