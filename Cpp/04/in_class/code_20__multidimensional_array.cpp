
#include <iostream>


/// The base case of container.
template< typename T, int... Extents >
struct multi_array
{
	static_assert( false, 
			"Implementation is placed only in the specializations." );
};

/// Specialization for extracting the first extent.
template< typename T, int Ext1, int... Extents >
struct multi_array< T, Ext1, Extents... >
{
	multi_array< T, Extents... > data[ Ext1 ];
};

/// Specialization, when all extents are extracted.
template< typename T >
struct multi_array< T >
{
	T data;  // The final cell
};


// Pay attention, rank of the 'multi_array' should not necessarily be known, 
//    at the moment of writing the program.


int main( int argc, char* argv[] )
{
	// Part 1
	{
		multi_array< float, 5, 4, 3 > y;

		y.data[ 2 ].data[ 0 ].data[ 1 ].data = 5.27f;

		static_assert( sizeof(y) == sizeof(float)*5*4*3, 
				"Check of size of 'multi_array' failed." );
	}

	return 0;
}
