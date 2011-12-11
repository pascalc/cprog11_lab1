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

	static std::size_t size2containers(std::size_t) const;
	static std::size_t index2container(index) const; // Move to proxy?
	static std::size_t index2bit(index) const; // Move to proxy?

	void check_range(index) const; // throw std::out_of_range("Index out of range");

	struct proxy {
		friend class Vector<bool>;

		bit_container& m_container;
		std::size_t m_bit;
		proxy();
		proxy(bit_container& container, std::size_t bit) :
			m_container(container),
			m_bit(bit) { }
		
		public:
			proxy& operator=(bool value) {
				m_container = 
				return true;
			}
			/*
			m_container = 1001 1000[2] (152[10]), m_bit = 5 
			*/
			bool operator() const {
				return (m_container >> (m_bit-1) ) & 1;
			}

	};

public:
	Vector<bool>() :
		m_size(0),
		m_data(0) {}

	explicit Vector<bool>(std::size_t size) :
		m_size(size),
		m_data(size2containers(size)) {}

	explicit Vector<bool>(std::size_t size, bool initial_value) :
		m_size(size),
		m_data(size2containers(size), initial_value ? ALL_BITS_INT : 0) {}

	Vector<bool>(const Vector& copy) : 
		m_size(copy.size()),
		m_data(copy.data) { }
	
	~Vector<bool>() {}

	/** reading **/
	const operator[](index) const;
	std::size_t size() const;

	/** writing **/
	Vecto<bool>& operator=(const Vector&); 
	proxy& operator[](index);
	Vector<bool>& push_back(bool);
	void clear();
};

#endif

static std::size_t Vector<bool>::size2containers(std::size_t size) const {
	return (size / NR_BITS_INT) + 1;
}

static std::size_t Vector<bool>::index2container(index i) const {
	return i / NR_BITS_INT;
}

static std::size_t Vector<bool>::index2bit(index i) const {
	return i % NR_BITS_INT; // (i+1)?
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

const bool Vector<bool>::operator[](index i) const {
	check_range(i);
	return proxy(m_data[index2container(i)], index2bit(i))();
}

Vector<bool>::proxy& Vector<bool>::operator[](index i) {
	check_range(i);
	return proxy(m_data[index2container(i)], index2bit(i));
}

std::size_t vector<bool>::size() const {
	return m_size;
}

vector<bool>& Vector<bool>& push_back(bool elem) {
	++size;
	if(size % NR_BITS_INT == 0) {
		m_data.push_back(0);
	}
	(*this)[size-1] = elem;
	return *this;
}

void Vector<bool>::clear() {
	m_size = 0;
	m_data.clear();
}