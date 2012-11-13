#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <stdexcept>
#include <iostream>

using namespace std;

#define INITIAL_CAPACITY 20

template<class T>
class Vector {
	typedef uint index;

	private:
		std::size_t m_capacity, m_size;
		T* m_data, m_first, m_last;

		void grow() {
			size_t new_capacity = 2 * m_capacity; 
			T* new_data = new T[new_capacity];
			for(size_t i = 0; i < m_size; ++i) {
				new_data[i] = m_data[i];
			}

			delete [] m_data;
			m_capacity = new_capacity;
			m_data = new_data;
		}
	
	public:
		Vector() : 
			m_capacity(INITIAL_CAPACITY), 
			m_size(0), 
			m_data(new T[m_capacity]),
			m_first(0),
			m_last(0) {}

		// Constructor creates Vector which size elements to be hold
		explicit Vector(size_t size) : 
			m_capacity(INITIAL_CAPACITY + 2*size),
			m_size(size), 
			m_data(new T[m_capacity]),
			m_first(0),
			m_last(0) 
		{
			for(size_t i = 0; i < m_size; ++i)
				m_data[i] = T();
		}

		// Constructor creates Vector with size 'size' and initiates all elements to 'val'
		explicit Vector(size_t size, const T& val) :
			m_capacity(INITIAL_CAPACITY + 2*size), 
			m_size(size),
			m_data(new T[m_capacity]),
			m_first(0),
			m_last(m_size-1)
		{
			for(size_t i = 0; i < m_size; ++i)
				m_data[i] = val;
		}

		// Copy constructor
		Vector(const Vector& v) :
			m_capacity(v.capacity()),
			m_size(v.size()),
			m_data(new T[m_capacity]),
			m_first(0),
			m_last(0)
		{
			for(size_t i = 0; i < m_size; ++i)
				m_data[i] = v[i];
		}


		~Vector() { delete [] m_data; }
		
		const T& operator[](index i) const {
		    if(i >= m_size)
				throw std::out_of_range ("Index out of range");    	
		    return m_data[i];
		}

		
		T& operator[](index i) {
		    if(i >= m_size)
		    	throw std::out_of_range ("Index out of range");
		    return m_data[i];
		}

		
		Vector& operator=(const Vector& copy) {
			if(this != &copy) {
				m_size = copy.size();
				m_capacity = copy.capacity();
				m_data = new T[m_capacity];
			
			for(size_t i = 0; i < m_size; i++)
				(*this)[i] = copy[i];
			
			}
			return *this;
		}

		void push_back(const T& elem) {
			if(++m_size >= m_capacity) 
				grow();
			m_data[m_size-1] = elem; 
		}

		Vector& insert(index i, const T& elem) {
			if(i >= m_size) {
				push_back(elem);
			} else {
				if(m_size >= m_capacity)
					grow();
				
				//Copy everything from i to i+1 (zero or one index??)
				// shift all the elements to the right, right by one
				size_t j = size()-1;
				while(true) {
					T tmp = m_data[j];
					m_data[j+1] = tmp;
					if(j == i)
						break;
					j--;
				}
				m_data[i] = elem;
				m_size++;
			}
			return *this;
		}

		Vector& erase(index i) {
			if(i >= m_size) {
				throw std::out_of_range("Out of range!");
			}

			if(m_size == 1) {
				return clear();
			}
			
			if (i < m_size-1) {
				// shift all the elements to the right, left by one
				for (size_t j = i+1; j < m_size; ++j) {
					T tmp = m_data[j];
					m_data[j-1] = tmp;
				}
			}
			
			--m_size;
			return *this;
		}

		Vector& clear() { 
			m_size = m_first = m_last = 0;
			return *this;
		}

		
		size_t size() const { 
			return m_size;
		}

		size_t capacity() const {
			return m_capacity;
		}

		Vector& sort() {
			sort(true);
		}

		Vector& sort(bool ascending) 
		{
			if (ascending) {
				std::sort(m_data,m_data+m_size);
			} else {
				std::sort(std::reverse_iterator<T*>(m_data+m_size),std::reverse_iterator<T*>(m_data));
			}
			return *this;	
		}
	};