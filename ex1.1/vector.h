#include <iostream>
#include <stdexcept>
#include <string.h>
#include <algorithm>

#define INITIAL_SIZE 100

template <typename T>
class Vector {
private:
	T * start;
	T * next;
	T * end; 
	size_t mCapacity;

	// Create a new array with capacity = this.capacity+INCREMENT_SIZE,
	// and copy all our old values into it
	void expand() {
		size_t new_capacity = mCapacity + 1.5*mCapacity;
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
	Vector<T>() : 
		mCapacity(INITIAL_SIZE), 
		start( new T[mCapacity]() ), 
		next(start), 
		end(start+mCapacity) { }

	// Standard constructor -- elements intialised to T()
	explicit Vector<T>(size_t initial_size) : 
		mCapacity(2*initial_size), 
		start( new T[mCapacity]() ), 
		next(start), 
		end(start+mCapacity)	
	{
		for (size_t i = 0; i < initial_size; i++) {
			*next = T();
			next++;
		}
	}

	// Standard constructor -- elements intialised to T initial_value
	explicit Vector<T>(size_t initial_size, T initial_value) : 
		mCapacity(2*initial_size),
		start( new T[mCapacity]() ),
		next(start),
		end(start+mCapacity)	
	{
		for (size_t i = 0; i < initial_size; i++) {
			*next = initial_value;
			next++;
		}
	}

	// Copy constuctor
	Vector<T>(const Vector<T>& copy) : 
		mCapacity(copy.capacity), 
		start( new T[mCapacity]()), 
		next(start), 
		end(start+mCapacity)	
	{
		// Allocate a new array of the appropriate mCapacity and populate it
		size_t size = copy.size();
		for (size_t i = 0; i < size; i++) {
			*next = copy[i];
			next++;
		}
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
			size_t j = size()-1;
			while(true) {
				T tmp = start[j];
				start[j+1] = tmp;
				if(j == index)
					break;
				j--;
			}
			next++;
			start[index] = element;
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
		// If last element, just clear the array
		if (size() == 1) {
			return clear();
		}
		// If it's not the last index, we need to shift
		if (index < size()-1) {
			// shift all the elements to the right, left by one
			for (size_t i = index+1; i < size(); i++) {
				T tmp = start[i];
				start[i-1] = tmp;
			}
		}
		next--;
		return *this;
	}
	
	// CLEAR all elements from the vector
	Vector<T>& clear() {
		next = start;
		return *this;
	}
	
	// SORT the elements in this vector
	Vector<T>& sort(bool ascending=true) {
		if (ascending) {
			std::sort(start,start+size());
		} else {
			std::sort(std::reverse_iterator<T*>(start+size()),std::reverse_iterator<T*>(start));
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
		mCapacity = rhs.capacity();
		start = new T [mCapacity];
		next = start;
		size_t size = rhs.size();
		for (size_t i = 0; i < size; i++) {
			*next = rhs[i];
			next++;
		}
		end = start + mCapacity;
		return *this;
	}
};