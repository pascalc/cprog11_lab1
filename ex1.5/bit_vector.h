#ifndef BITVECTOR_H
#define BITVECTOR_H

#include <iostream>
#include <iterator>
#include <algorithm>

#include "../1.5/vector.h"

using namespace std;

template <>
class Vector<bool> {
	typedef unsigned int container_t;
	typedef std::size_t index_t;
	
	static const std::size_t BITS_IN_CONTAINER = sizeof(container_t)*8; 
	static const std::size_t ALL_BITS_SET = 0xFFFFFFFF; // 2^31-1, 

	std::size_t m_size;
	Vector<container_t> m_data;

	static std::size_t size2containers(std::size_t);
	std::size_t index2container(index_t) const;
	std::size_t index2bit(index_t) const;

	void check_range(index_t) const;
	void clear_unused_bits();

	struct proxy {
		private:
			container_t& m_container;
			std::size_t m_bit;
			proxy();
			proxy(container_t& container, std::size_t bit);
		public:
			proxy& operator=(bool value);
			proxy& operator=(const proxy& p);
			operator bool() const;
	};
public:
	// iterator traits http://www.cplusplus.com/reference/std/iterator/iterator_traits/
	typedef size_t difference_type;
	typedef bool value_type;
	typedef random_access_iterator_tag iterator_category;

	typedef const bool* const_pointer;
	typedef const bool& const_reference;
	//http://www.cplusplus.com/reference/std/iterator/RandomAccessIterator/
	class const_iterator : public std::iterator<std::random_access_iterator_tag, value_type> {
		protected:
			friend class Vector<bool>;
			const Vector<bool>* m_vector;
			std::size_t m_index;
			const_iterator(const Vector<bool>& v, std::size_t i);
		public:
			const_iterator(const const_iterator& copy);
			virtual ~const_iterator();
			const_iterator& operator=(const const_iterator& cit);
			bool operator==(const const_iterator& cit) const;
			bool operator!=(const const_iterator& cit) const;
			bool operator*() const;
			const_iterator& operator+=(std::size_t value);
			const_iterator& operator-=(std::size_t value);
			const_iterator& operator++();
			const_iterator& operator--();
			const_iterator operator-(std::size_t value) const;
			const_iterator operator+(std::size_t value) const;
			const_iterator operator++(int);
			const_iterator operator--(int);
			difference_type operator-(const const_iterator& cit) const;
	};

	typedef bool& reference;
	typedef bool* pointer;
	class iterator : public const_iterator {
		public:
			typedef proxy& reference;
			iterator(iterator& copy);
			iterator(const_iterator& copy);
			bool operator*();
	};

public:
	Vector<bool>();
	explicit Vector<bool>(std::size_t size);
	explicit Vector<bool>(std::size_t size, bool initial_value);
	Vector<bool>(const Vector& copy);
	~Vector<bool>() {}

	/** reading **/
	bool operator[](index_t) const;
	std::size_t size() const;

	/** writing **/
	Vector<bool>& operator=(const Vector&); 
	proxy operator[](index_t);
	void push_back(bool); // Vector<bool>&
	void clear();

	void sort();
	void sort(bool);

	unsigned int get_int();

	const_iterator begin() const;
	const_iterator end() const;

	Vector<bool> operator&(const Vector<bool>&) const;
	Vector<bool> operator|(const Vector<bool>&) const;
	Vector<bool> operator^(const Vector<bool>&) const;
	Vector<bool> operator~() const;
	int weight1() const;
	int weight2() const;
	int weight3() const;
};

#endif