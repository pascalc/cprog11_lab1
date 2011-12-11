#ifndef BOOL_VECTOR_H
#define BOOL_VECTOR_H

#include "../ex1.1/vector.h"

#include <iostream>

template <>
class Vector<bool> {
	typedef unsigned int bit_container;
	typedef std::size_t index;

	static const std::size_t NR_BITS_INT = 32;
	static const std::size_t ALL_BITS_INT = 0xFFFFFFFF; // 2^31-2, 

	std::size_t m_size;
	Vector<bit_container> m_data;

	static std::size_t nr_containers(std::size_t) const;
	static std::size_t index2byte(index) const; // MOve to proxy?
	static std::size_t index2bit(index) const; // Move to proxy?

	void check_range(index) const throw std::out_of_range("Index out of range");

	struct proxy {
		friend class Vector<bool>;

		bit_container& m_container;
		std::size_t m_bit;
		proxy();
		proxy(bit_container& container, std::size_t bit) :
			m_container(container),
			m_bit(bit) { }
		
		public:
			bool operator=(bool value) {
				m_container = 
				return true;
			}

	};

public:
	Vector<bool>() :
		m_size(0),
		m_data(0) {}

	explicit Vector<bool>(std::size_t size) :
		m_size(size),
		m_data(nr_containers(size)) {}

	explicit Vector<bool>(std::size_t size, bool initial_value) :
		m_size(size),
		m_data(nr_containers(size), initial_value ? ALL_BITS_INT : 0) {}

	Vector<bool>(const Vector& copy) : 
		m_size(copy.size()),
		m_data(copy.data) { }
	
	~Vector<bool>() {}

	Vecto<bool>& operator=(const Vector&);
	const proxy& operator[](index) const;
	proxy& operator[](index);
	std::size_t size() const;
	Vector<bool>& push_back(bool);
	Vector<bool>& insert(index, bool);
	bool pop_back(bool);
	void clear();
};

#endif

static std::size_t Vector<bool>::nr_containers(std::size_t size) const {
	return (size / NR_BITS_INT) + 1;
}

static std::size_t Vector<bool>::index2byte(index i) const {
	return i / NR_BITS_INT;
}

static std::size_t Vector<bool>::index2bit(index i) const {
	return i % NR_BITS_INT;
}


void Vector<bool>::check_range(index i) const {
	if(i >= m_size) throw std::out_of_range("Index out of range");
}

Vector<bool>& Vector<bool>::operator=(const Vector<bool>& rhs) {
	if(this != &rhs) {
		m_size = rhs.size();
		m_data = rhs.m_data();
	}
	return *this;
}

const Vector<bool>::proxy& Vector<bool>::operator[](index i) const {
	check_range(i);

}

Vector<bool>::proxy& Vector<bool>::operator[](index i) {
	check_range(i);
}

std::size_t vector<bool>::size() const {
	return m_size;
}

vector<bool>& Vector<bool>& push_back(bool elem) {
	return *this;
}

vector<bool>& Vector<bool>& insert(index i, bool elem) {
	check_range(i);
	return *this;
}

bool Vector<bool>::pop_back() {
	if(m_size == 0) throw std::out_of_range("Error! Empty vector")
	return (*this)[--m_size];
}

void Vector<bool>::clear() {
	m_data.clear();
	m_size = 0;
}