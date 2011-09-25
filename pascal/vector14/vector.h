#ifndef VECTOR_14_H
#define VECTOR_14_H

#include <stdlib.h>

class Vector {
public:
	explicit Vector(size_t size);
	Vector(const Vector& copy);
	~Vector();

	// Functions
	size_t size() const;
	const int& operator[](int index) const;
	int& operator[](int index);
	Vector& operator=(const Vector& rhs);
};
#endif