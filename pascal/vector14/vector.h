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
		int & ref;
		array_proxy(int & r) : ref(r) {}
		void operator = (int value) {
			ref = value;
		}
		operator int() const{
			return ref;
		}
		// Prefix ++
		int operator ++ () {
			return ++ref;
		}
		// Postfix ++
		int operator ++ (int i) {
			return ref++;
		}
	};

	// Functions
	unsigned int size() const;
	int operator[](int index) const;
	array_proxy operator[](int index);
	Vector& operator=(const Vector& rhs);
};
#endif