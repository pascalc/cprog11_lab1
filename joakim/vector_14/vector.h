#ifndef VECTOR_14_H
#define VECTOR_14_H

#include <stdlib.h>
#include <string.h>
using namespace std;

#define INIT_SIZE 100

class Vector {
	typedef unsigned int uint_t;

	public:
		// Constructors
		Vector() : my_size(0), capacity(INIT_SIZE), array(new uint_t) {}
		
		explicit Vector(size_t s) : my_size(s), capacity(2*s), array(new uint_t[capacity])
		{
			//for(size_t i = 0; i < my_size; i++)
		 	//	array[i] = 0;
		 	memset(array, 0, my_size * sizeof(unsigned int));
		}
		Vector(const Vector &v) : my_size(v.my_size), capacity(v.capacity), array(new uint_t[capacity])
		{
			//for(size_t i = 0; i < my_size; i++)
		 	//	array[i] = v[i];
		 	memcpy(array, v.array, my_size * sizeof(unsigned int));
		}
		// Deconstructor
		~Vector() 
		{
			delete [] array;	
		}

		// Functions
		const unsigned int operator[](unsigned int i) const;// throw std::out_of_range ("Out of range");
		unsigned int& operator[](unsigned int i);// throw std::out_of_range ("Out of range");
		Vector& operator=(const Vector &v);
		unsigned int size() const; //

	private:	
		// Variables
		unsigned int my_size;		// size of the vector
		unsigned int capacity;	// capacity of the vector
		unsigned int * array;
};
#endif