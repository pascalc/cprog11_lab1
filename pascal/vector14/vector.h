#ifndef VECTOR_14_H
#define VECTOR_14_H

#include <stdlib.h>

class Vector {
private:
	private:
	// Internal 'backbone' array
	int * array;
	size_t capacity;

public:
	explicit Vector(size_t size);
	Vector(const Vector& copy);
	~Vector();

	// Functions
	size_t size() const;
	const int& operator[](unsigned int index) const;
	int& operator[](unsigned int index);
	Vector& operator=(const Vector& rhs);
};
#endif