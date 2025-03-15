
// Ordinary implementation of dynamic array.
template< typename T >
class vector
{
private:
	T* _data;   // The dynamic array
	int _size;  // Its logical length

public:
	void push_back( const T& x )
		{ /* Reallocate if needed */  _data[_size++] = x; }

	void pop_back()
		{ /* Check if empty */  --_size; }

	T& operator[]( int index )
		{ return _data[ index ]; }

	const T& operator[]( int index ) const
		{ return _data[ index ]; }

	// Other methods ...
};


// What if user wants 'vector<bool>' ?
// Every bool occupies 1 or even 2 bytes (probably cause of alignment).
// We don't want to waste 7/8 or 15/16 of memory?
// Can we organize array of 'bool' more efficient?


// Specialization of dynamic array for booleans.
template<>
class vector< bool >
{
private:
	unsigned char* _data;  // The dynamic array
	int _size;             // How many first bits do we use.

public:
	void push_back( bool x ) {
		//
		// How to implement this?
		//
	}

	bool operator[]( int index ) const {
		const int byte_index = index / 8;
		const int bit_index = index % 8;
		return (_data[ byte_index ] >> bit_index) & 0x01;
	}

	bool& operator[]( int index ) {
		//
		// How to implement this?
		//
	}

	// Other methods ...
};


//
// Specialization of function templates
//

// General implementation of sorting
template< typename T >
void sort( T* data, int length )
{
	// Here we do Selection sort for general case, in order 
	// to reduce number of assignments to minimum.

	for ( int i = 0; i < length - 1; ++i ) {
		int min_pos = i;
		for ( int j = i+1; j < length; ++j )
			if ( data[j] < data[min_pos] )
				min_pos = j;
		if ( min_pos != i ) {
			T temp = data[i];
			data[i] = data[min_pos];
			data[min_pos] = temp;
		}
	}
}

// Specialization for sorting pointers
template< typename T >
void sort< T* >( T** data, int length )
{
	// Some other, more efficient sorting algorithm.
}

// Specialization for sorting C-style strings
template<>
void sort< const char* >( const char** data, int length )
{
	// Here we will use 'strcmp()' for comparison.
}


// We see that a template can have multiple specializaitons.
//
// Compiler will pick the specialization which BETTER MATCHES the 
// arguments list.
