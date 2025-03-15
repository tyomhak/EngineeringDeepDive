

// Implementing dynamic arrays for various types.

class ints_vector
	{ /* Some implementation */ };

class doubles_vector
	{ /* Some implementation */ };

class strings_vector
	{ /* Some implementation */ };


// Implementing rectangles for various coordinate types.

class int_rectangle
	{ /* Some implementation */ };

class double_rectangle
	{ /* Some implementation */ };

class rational_rectangle
	{ /* Some implementation */ };


// Calculating maximum of 2 values

int max_of_ints( int a, int b )
	{ return a < b ? b : a; }

double max_of_doubles( double a, double b )
	{ return a < b ? b : a; }

long long max_of_long_longs( long long a, long long b )
	{ return a < b ? b : a; }


// Bubble sort

void bubble_sort_ints( int* begin, int* end )
	{ /* Some implementation. */ }

void bubble_sort_doubles( double* begin, double* end )
	{ /* Some implementation. */ }

void bubble_sort_strings( char** begin, char** end )
	{ /* Some implementation. */ }


//
// Solutions with templates
//

template< typename T >
class vector
	{ /* Here we use 'T' inside. */ };

template< typename CoordType >
class rectangle
	{ /* Here coordinates are of type 'CoordType'. */ };

template< typename T >
T max( const T& a, const T& b )
	{ return a < b ? b : a; }

template< typename T >
void bubble_sort( T* begin, T* end )
	{ /* Implementation */ }


// Note, the templates are NOT READY TO USE yet... We must substitude 'T'
// with something, in order to get usable class (or function).
