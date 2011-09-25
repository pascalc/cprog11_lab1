#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>

#define INCREMENT_SIZE 20

template <class T>
class Vector {
private:
	T * start;
	T * next;
	T * end; 
	size_t mCapacity;

	// Create a new array with capacity = this->capacity+INCREMENT_SIZE,
	// and copy all our old values into it
	void expand() {
		size_t new_capacity = mCapacity + INCREMENT_SIZE;
		T * new_start = new T [new_capacity];
		T * new_next = new_start;
		for (size_t i = 0; i < size(); i++) {
			*new_next = start[i];
			new_next++;
		}
		T * new_end = new_start + new_capacity;

		delete [] start;

		start = new_start;
		next = new_next;
		end = new_end;
		mCapacity = new_capacity;
	}	


public:
	// Default constructor -- empty vector
	Vector<T>() {
		mCapacity = 0;
		start = 0;
		next = 0;
		end = 0;
	}

	// Standard constructor -- elements intialised to T()
	explicit Vector<T>(size_t initial_size) {
		mCapacity = 2*initial_size;
		start = new T [mCapacity];
		next = start;
		for (size_t i = 0; i < initial_size; i++) {
			*next = T();
			next++;
		}
		end = start + mCapacity;
	}

	// Standard constructor -- elements intialised to T initial_value
	explicit Vector<T>(size_t initial_size, T initial_value) {
		mCapacity = 2*initial_size;
		start = new T [mCapacity];
		next = start;
		for (size_t i = 0; i < initial_size; i++) {
			*next = initial_value;
			next++;
		}
		end = start + mCapacity;
	}

	// Copy constuctor
	Vector<T>(const Vector& copy) {
		// Allocate a new array of the appropriate mCapacity and populate it
		this->mCapacity = copy.capacity();
		start = new T [mCapacity];
		next = start;
		size_t size = copy.size();
		for (size_t i = 0; i < size; i++) {
			*next = copy[i];
			next++;
		}
		end = start + mCapacity;
	}

	// Deconstructor
	~Vector<T>() {
		delete [] start;
	}

	// Return the current size of this Vector
	size_t size() const {
		return next-start;
	}

	// Return the current capacity of this Vector
	size_t capacity() const {
		return mCapacity;
	}

	// Read operator
	const T& operator[](size_t index) const {
		if (index >= size() || index < 0) {
			throw std::out_of_range("Out of range!");
		}
		return start[index];	
	}
	
	// Write operators
	
	// SET the value at an index
	T& operator[](size_t index) {
		if (index >= size() || index < 0) {
			throw std::out_of_range("Out of range!");
		}
		return start[index];	
	}
	
	// INSERT and SHIFT at an index: eg v = [0,1,2,3]; v.insert(0,-1) -> v = [-1,0,1,2,3]
	Vector<T>& insert(size_t index, T element) {
		if (index > size() || index < 0) {
			throw std::out_of_range("Out of range!");
		}
		if (index == size()) {
			push_back(element);
		} else {
			// If we are full
			if(next == end){
				expand();	
			}
			// shift all the elements to the right, right by one
			T * dest = &start[index+1];
			T * source = &start[index];
			size_t bytes = (size() - index) * sizeof(T);
			memmove(dest,source,bytes);

			start[index] = element;
			next++;
		}
		return *this;
	}
	
	// APPEND to the vector
	T push_back(T element) {
		if (next == end) {
			expand();
		} 
		*next = element;
		next++;	
		return element;	
	}
	
	// ERASE an element from the vector
	Vector<T>& erase(size_t index) {
		if (index >= size() || index < 0) {
			throw std::out_of_range("Out of range!");
		}
		// shift all the elements to the right, left by one
		T * dest = &start[index];
		T * source = &start[index+1];
		size_t bytes = (size() - index+1) * sizeof(T);
		memmove(dest,source,bytes);

		next--;
		return *this;
	}
	
	// CLEAR all elements from the vector
	Vector<T>& clear() {
		delete [] start;
		start = new T [mCapacity];
		next = start;
		end = start + mCapacity;
		return *this;
	}
	
	// SORT the elements in this vector
	Vector<T>& sort(bool ascending=true) {
		if (ascending) {
			std::sort(start,start+size());
		} else {
			std::sort(start,start+size(), std::greater<int>());
		}
		return *this;	
	}

	// Assignment operator
	Vector<T>& operator=(const Vector<T>& rhs) {
		// Trivial case, v1 = v1
		if (this == &rhs) {
			return *this;
		}
		
		// Otherwise copy the rhs array into our own
		this->mCapacity = rhs->capacity();
		start = new T [mCapacity];
		next = start;
		size = rhs->size();
		for (size_t i = 0; i < size; i++) {
			*next = rhs[i];
			next++;
		}
		end = start[mCapacity];
		return *this;
	}
};