#ifndef BITVECTOR_H
#define BITVECTOR_H

#include "../ex1.1/vector.h"

#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

template <>
class Vector<bool> {
	typedef unsigned int bit_container;
	typedef std::size_t index;

	static const std::size_t NR_BITS_INT = 32;
	static const std::size_t ALL_BITS_INT = 0xFFFFFFFF; // 2^31-1, 

	std::size_t m_size;
	Vector<bit_container> m_data;

	// TODO: Could be declared static
	std::size_t size2containers(std::size_t);
	std::size_t index2container(index) const;
	std::size_t index2bit(index) const;

	void check_range(index) const; // throw std::out_of_range("Index out of range");

	struct proxy {
		friend class Vector<bool>;	// enables use of typedefs in Vector<bool>

		bit_container& m_container;
		std::size_t m_bit;
		proxy();

		proxy(bit_container& container, std::size_t bit) :
			m_container(container),
			m_bit(bit) { }
		
		public:
			proxy& operator=(bool value) {
				m_container = (m_container & ~(1 << m_bit)) | (value << m_bit); 
				return *this;
			}

			proxy& operator=(const proxy& p) {
				*this = static_cast<bool>(p);
				return *this;
			}
			/**
			* m_container = 1001 1000[2] (152[10]), m_bit = 5. 
			* (1001 1000 >> 5 --> 100. 100 & 1 = false
			**/
			operator bool() const {
				return (m_container >> m_bit) & 1;
			}

	};
public:
	// iterator traits http://www.cplusplus.com/reference/std/iterator/iterator_traits/
	typedef size_t difference_type;
	typedef bool value_type;
	// typedef bool& reference;
	// typedef bool* pointer;
	typedef random_access_iterator_tag iterator_category;

	typedef const bool* const_pointer;
	typedef const bool& const_reference;
	//http://www.cplusplus.com/reference/std/iterator/RandomAccessIterator/
	class const_iterator : public std::iterator<std::random_access_iterator_tag, bool> {
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

			// bool operator<(const const_iterator& cit) const {
			// 	return *this < *cit;
			// }

			bool operator*() const {
				return (*m_vector)[m_index];
			}

			// bool* operator->() const {
			// 	return &(operator*());
			// }

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

public:
	const_iterator begin() const;
	const_iterator end() const;

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
	bool operator[](index) const;
	std::size_t size() const;

	/** writing **/
	Vector<bool>& operator=(const Vector&); 
	proxy operator[](index);
	void push_back(bool); // Vector<bool>&
	void clear();

	void sort();
	void sort(bool);

	unsigned int get_int();

	Vector<bool> operator&(const Vector<bool>& rhs) const;
	Vector<bool> operator|(const Vector<bool>& rhs) const;
	Vector<bool> operator^(const Vector<bool>& rhs) const;
	int weight1() const;
	int weight2() const;
	int weight3() const;
};

#endif

Vector<bool>::const_iterator Vector<bool>::begin() const {
	return const_iterator(*this, size_t(0) );
}

Vector<bool>::const_iterator Vector<bool>::end() const {
	return const_iterator(*this, m_size-1);
}

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

bool Vector<bool>::operator[](index i) const {
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

void Vector<bool>::push_back(bool elem) { // Vector<bool>& 
	m_size++;
	if(m_size % NR_BITS_INT == 1) {
		m_data.push_back(0);
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
	//xCount = x - ((x >> 1) & 033333333333) - ((x >> 2) & 011111111111);
	//nr_ones = ((xCount + (xCount >> 3)) & 030707070707) % 63;

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
	if(m_size > NR_BITS_INT) {
		throw std::logic_error("Oversize, unable to convert to integer");
	}
	if(m_size == 0) {
		return 0;
	}
	return m_data[0];
}

Vector<bool> Vector<bool>::operator&(const Vector<bool>& rhs) const {
	Vector<bool> ret(*this);
	for(std::size_t i = 0; i < m_size; ++i) {
		ret[i] = ret[i] & rhs[i];	
	}	
	return ret;
}

Vector<bool> Vector<bool>::operator|(const Vector<bool>& rhs) const {
	Vector<bool> ret(*this);
	for(std::size_t i = 0; i < m_size; ++i) {
		ret[i] = ret[i] | rhs[i];	
	}	
	return ret;	
}

Vector<bool> Vector<bool>::operator^(const Vector<bool>& rhs) const {
	Vector<bool> ret(*this);
	for(std::size_t i = 0; i < m_size; ++i) {
		ret[i] = ret[i] ^ rhs[i];
	}	
	return ret;
}

int Vector<bool>::weight1() const {
	return 0;
}
int Vector<bool>::weight2() const {
	return 0;
}

int Vector<bool>::weight3() const {
	return 0;
}