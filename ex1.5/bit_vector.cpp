#include <iostream>
#include <iterator>
#include <algorithm>

#include "bit_vector.h"

using namespace std;

struct Vector<bool>::proxy {
	public:
		proxy& operator=(bool value) {
			m_container = (m_container & ~(1 << m_bit)) | (value << m_bit); 
			return *this;
		}

		proxy& operator=(const proxy& p) {
			*this = static_cast<bool>(p);
			return *this;
		}
		
		inline operator bool() const { return (m_container >> m_bit) & 1; }

};

class Vector<bool>::const_iterator : public std::iterator<std::random_access_iterator_tag, value_type> {
	private:
		friend class Vector<bool>;
		const Vector<bool>* m_vector;
		std::size_t m_index;

		const_iterator(const Vector<bool>& v, std::size_t i) : 
			m_vector(&v),
			m_index(i) {}
	
	public:
		const_iterator(const const_iterator& copy) :
			m_vector(copy.m_vector),
			m_index(copy.m_index) {}

		const_iterator& operator=(const const_iterator& cit) {
			if(*this != cit) {
				m_vector = cit.m_vector;
				m_index = cit.m_index;
			}
			return *this;
		}

		bool operator==(const const_iterator& cit) const {
			return m_vector == cit.m_vector && m_index == cit.m_index;
		}

		bool operator!=(const const_iterator& cit) const {
			return !(*this == cit);
		}

		bool operator*() const {
			return (*m_vector)[m_index];
		}

		const_iterator& operator+=(std::size_t value) {
			m_index += value; return *this;
		}

		const_iterator& operator-=(std::size_t value) {
			m_index -= value; return *this;
		}

		const_iterator& operator++() { 
			m_index++; return *this; 
		}

		const_iterator& operator--() { 
			m_index--; return *this; 
		}

		const_iterator operator-(std::size_t value) const {
			const_iterator copy(*this);
			copy.m_index -= value;
			return copy;
		}

		const_iterator operator+(std::size_t value) const {
			const_iterator copy(*this);
			copy.m_index += value;
			return copy;
		}
		
		const_iterator operator++(int) { 
			const_iterator copy(*this);
			operator++();
			return copy; 
		}

		const_iterator operator--(int) {
			const_iterator copy(*this);
			operator--();
			return copy;
		}

		difference_type operator-(const const_iterator& cit) const {
			return (m_index - cit.m_index);
		}
};

class Vector<bool>::iterator : public Vector<bool>::const_iterator {
		public:
			iterator(iterator& copy) : 
				const_iterator(*copy.m_vector, copy.m_index) {}

			iterator(const_iterator& copy) :
				const_iterator(*copy.m_vector, copy.m_index) {}
			
			bool operator*() {
				return (*m_vector)[m_index];
			}
	};

Vector<bool>::Vector() :
	m_size(0),
	m_data(0) {}

Vector<bool>::Vector(std::size_t size) :
	m_size(size),
	m_data(size2containers(size)) { clear_unused_bits(); }

Vector<bool>::Vector(std::size_t size, bool initial_value) :
	m_size(size),
	m_data(size2containers(size), initial_value ? ALL_BITS_SET : 0) { clear_unused_bits(); }

Vector<bool>::Vector(const Vector& copy) : 
	m_size(copy.size()),
	m_data(copy.m_data) { clear_unused_bits(); }

Vector<bool>::const_iterator Vector<bool>::begin() const {
	return const_iterator(*this, 0);
}

Vector<bool>::const_iterator Vector<bool>::end() const {
	return const_iterator(*this, m_size-1);
}

std::size_t Vector<bool>::size2containers(std::size_t size) {
	return (size / BITS_IN_CONTAINER) + 1;
}

std::size_t Vector<bool>::index2container(index_t i) const {
	return i / BITS_IN_CONTAINER;
}

std::size_t Vector<bool>::index2bit(index_t i) const {
	return i % BITS_IN_CONTAINER; // (i+1)?
}

void Vector<bool>::check_range(index_t i) const {
	if(i >= m_size) throw std::out_of_range("Index out of range");
}

void Vector<bool>::clear_unused_bits() {
	std::size_t last_element = (m_size > 0) ? m_data.size() - 1 : 0;
	for(std::size_t i = (m_size - BITS_IN_CONTAINER); i < BITS_IN_CONTAINER; ++i)
		m_data[last_element] &= ~(1 << i); 
}

Vector<bool>& Vector<bool>::operator=(const Vector<bool>& rhs) {
	if(this != &rhs) {
		m_size = rhs.size();
		m_data = rhs.m_data;
	}
	return *this;
}

bool Vector<bool>::operator[](index_t i) const {
	check_range(i);
	return (m_data[index2container(i)] >> index2bit(i)) & 1; // proxy(..., ...)();
}

Vector<bool>::proxy Vector<bool>::operator[](index_t i) {
	check_range(i);
	return proxy(m_data[index2container(i)], index2bit(i));
}

std::size_t Vector<bool>::size() const {
	return m_size;
}

void Vector<bool>::push_back(bool elem) { // Vector<bool>& 
	++m_size;
	if(m_size % BITS_IN_CONTAINER == 1) {
		m_data.push_back(0);
		clear_unused_bits();
	}
	(*this)[m_size-1] = elem;
}

void Vector<bool>::clear() {
	m_size = 0;
	m_data.clear();
}

void Vector<bool>::sort() {
	sort(true);
}

void Vector<bool>::sort(bool ascending) {
	std::size_t nr_zeros = 0, i = 0;
	for(; i < m_size; ++i)
		if( (*this)[i] != ascending) ++nr_zeros;

	i = 0;
	for(; i < nr_zeros; ++i)
		(*this)[i] = !ascending;

	for(; i < m_size; ++i)
		(*this)[i] = ascending;
}

unsigned int Vector<bool>::get_int() {
	if(m_size > BITS_IN_CONTAINER) {
		throw std::logic_error("Oversize, unable to convert to integer");
	}
	if(m_size == 0) {
		return 0;
	}
	return m_data[0];
}

Vector<bool> Vector<bool>::operator&(const Vector<bool>& rhs) const {
	Vector<bool> res(*this);
	for(std::size_t i = 0; i < m_data.size(); ++i)
		res.m_data[i] &= rhs.m_data[i];
	
	return res;
}

Vector<bool> Vector<bool>::operator|(const Vector<bool>& rhs) const {
	Vector<bool> res(*this);
	for(std::size_t i = 0; i < m_data.size(); ++i)
		res.m_data[i] |= rhs.m_data[i];
	return res;
}

Vector<bool> Vector<bool>::operator^(const Vector<bool>& rhs) const {
	Vector<bool> res(*this);
	for(std::size_t i = 0; i < m_data.size(); ++i)
		res.m_data[i] ^= rhs.m_data[i];
	return res;
}

Vector<bool> Vector<bool>::operator~() const {
	Vector<bool> res(*this);
	for(std::size_t i = 0; i < m_data.size(); ++i)
		res.m_data[i] ^= ALL_BITS_SET;
	return res;
}

// Mathematical
int Vector<bool>::weight1() const {
	int nr_ones = 0;
	for(std::size_t i = 0; i < m_data.size(); ++i) {
		container_t x = m_data[i];
		int xCount = x - ((x >> 1) & 033333333333) - ((x >> 2) & 011111111111);
		nr_ones += ((xCount + (xCount >> 3)) & 030707070707) % 63;
	}
	return nr_ones;
}

// Count the right most one (least significant) in each iteration
int Vector<bool>::weight2() const {
	uint nr_ones = 0;
	for(std::size_t i = 0; i < m_data.size(); ++i) {
		container_t v = m_data[i];
		for (; v; nr_ones++) {
		  v &= v - 1; // clear the least significant bit set
		}	
	}
	return nr_ones;
}

int Vector<bool>::weight3() const {
	uint nr_ones = 0;
	for(std::size_t i = 0; i < m_data.size(); ++i) {
		container_t v = ~m_data[i];
		for (; v; nr_ones++) {
		  v &= v - 1; // clear the least significant bit set
		}	
	}
	return nr_ones;	
}