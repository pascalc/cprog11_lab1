#ifndef VECTOR_14_H
#define VECTOR_14_H

#include <stdlib.h>

class Vector {
	public:
		// Constructors
		Vector();
		explicit Vector(size_t s);
		Vector(const Vector &v);
		// Deconstructor
		~Vector();

		// Functions
		const unsigned int operator[](unsigned int i) const;// throw std::out_of_range ("Out of range");
		unsigned int& operator[](unsigned int i);// throw std::out_of_range ("Out of range");
		Vector& operator=(const Vector &v);
		unsigned int size() const; //

	private:	
		// Variables
		unsigned int capacity;	// capacity of the vector
		unsigned int my_size;		// size of the vector
		unsigned int * array;
};
#endif