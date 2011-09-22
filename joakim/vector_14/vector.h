//#ifndef VECTOR_14_H
//#define VECTOR_14_H

#include <stdlib.h>

class Vector {
	public:
		// Variables
		unsigned int capacity;	// capacity of the vector
		unsigned int size;		// size of the vector
		unsigned int * array;

		// Constructors
		Vector();
		explicit Vector(size_t s);
		explicit Vector(const Vector &v);
		// Deconstructor
		~Vector() { delete [] this->array; };

		// Functions
		const unsigned int operator[](unsigned int i) const; // throw (std::out_of_range);
		unsigned int& operator[](unsigned int i); // throw (std::out_of_range);
		Vector& operator=(const Vector &v);

	private:	
		// Functions
		void initiate(unsigned int * a);
};
//#endif