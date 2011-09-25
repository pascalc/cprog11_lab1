#ifndef VECTOR_14_H
#define VECTOR_14_H

#include <stdlib.h>

class Vector {
private:
	private:
	// Internal 'backbone' array
	unsigned int * array;
	size_t capacity;

public:
	explicit Vector();
	explicit Vector(size_t size);
	Vector(const Vector& copy);
	~Vector();

	// Functions
	size_t size() const;
	const unsigned int& operator[](unsigned int index) const;
	unsigned int& operator[](unsigned int index);
	Vector& operator=(const Vector& rhs);
};
#endif