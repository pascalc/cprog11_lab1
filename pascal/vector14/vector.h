#ifndef VECTOR_14_H
#define VECTOR_14_H

#include <stdlib.h>

class Vector {
public:
	// Constructors
	explicit Vector(unsigned int size);
	Vector(const Vector& copy);
	// Deconstructor
	~Vector();

	struct array_proxy {
		array_proxy(int & r);
		void operator = (int value);
		operator int() const;
		int operator ++ ();
		int operator ++ (int i);
	};

	// Functions
	unsigned int size() const;
	int operator[](int index) const;
	array_proxy operator[](int index);
	Vector& operator=(const Vector& rhs);
};
#endif