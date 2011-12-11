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

	// TODO: Should be declared static
	std::size_t size2containers(std::size_t);	// const removed because of container in proxy
	std::size_t index2container(index) const; // Move to proxy?
	std::size_t index2bit(index) const; // Move to proxy?

	void check_range(index) const; // throw std::out_of_range("Index out of range");

	struct proxy {
		bit_container& m_container;
		std::size_t m_bit;
		proxy();
		proxy(bit_container& container, std::size_t bit) :
			m_container(container),
			m_bit(bit) { }
		
		friend class Vector<bool>;	// enables use of typedefs in Vector<bool>
		public:
			proxy& operator=(bool value) {
				uint mask = 1 << m_bit; // align the indexed bit
				mask = value << m_bit;	// set mask according to value
				m_container = m_container | mask; 
				return *this;
			}
			/**
			* m_container = 1001 1000[2] (152[10]), m_bit = 5. 
			* (1001 1000 >> 5 --> 100. 100 & 1 = false
			**/
			bool operator()() const {
				return (m_container >> m_bit) & 1;
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
		m_data(copy.m_data) { }
	
	~Vector<bool>() {}

	/** reading **/
	const bool operator[](index) const;
	std::size_t size() const;

	/** writing **/
	Vector<bool>& operator=(const Vector&); 
	proxy operator[](index);
	Vector<bool>& push_back(bool);
	void clear();
};

#endif

std::size_t Vector<bool>::size2containers(std::size_t size) {
	return (size / NR_BITS_INT) + 1;
}

std::size_t Vector<bool>::index2container(index i) const {
	return i / NR_BITS_INT;
}

std::size_t Vector<bool>::index2bit(index i) const {
	return i % NR_BITS_INT; // (i+1)?
}


void Vector<bool>::check_range(index i) const {
	if(i >= m_size) throw std::out_of_range("Index out of range");
}

Vector<bool>& Vector<bool>::operator=(const Vector<bool>& rhs) {
	if(this != &rhs) {
		m_size = rhs.size();
		m_data = rhs.m_data;
	}
	return *this;
}

const bool Vector<bool>::operator[](index i) const {
	check_range(i);
	return (m_data[index2container(i)] >> index2bit(i)) & 1; // proxy(..., ...)();
}

Vector<bool>::proxy Vector<bool>::operator[](index i) {
	check_range(i);
	return proxy(m_data[index2container(i)], index2bit(i));
}

std::size_t Vector<bool>::size() const {
	return m_size;
}

Vector<bool>& Vector<bool>::push_back(bool elem) {
	++m_size;
	if(m_size % NR_BITS_INT == 0) {
		m_data.push_back(0);
	}
	(*this)[m_size-1] = elem;
	return *this;
}

void Vector<bool>::clear() {
	m_size = 0;
	m_data.clear();
}