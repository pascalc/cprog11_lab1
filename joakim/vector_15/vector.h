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
	private:
		// Variables
		size_t my_capacity;		// capacity of the vector
		size_t my_size;			// size of the vector
		T* array;					// underlaying array of type T (generic)
		
		void resize() 
		{
			size_t new_capacity = my_capacity + (1.5)*my_capacity; 
			T *new_array = new T[new_capacity];
			for(size_t i = 0; i < my_size; i++) {
				new_array[i] = array[i];
			}

			delete [] array;
			my_capacity = new_capacity;
			array = new_array;
		}
	
	public:
		Vector<T>() 
			: my_capacity(INITIAL_CAPACITY), my_size(0), array(new T[my_capacity])
		{
		}

		// Constructor creates Vector which size elements to be hold
		explicit Vector<T>(size_t size) 
			: my_capacity(INITIAL_CAPACITY + 2*size), my_size(size), array(new T[my_capacity]) 
		{
			for(size_t i = 0; i < my_size; i++)
				array[i] = T();
			//memset(array, T(), capacity * sizeof(T));
		}

		// Constructor creates Vector with size 'size' and initiates all elements to 'val'
		explicit Vector<T>(size_t size, T val) 
			: my_capacity(INITIAL_CAPACITY + 2*size), my_size(size),  array(new T[my_capacity])
		{
			for(size_t i = 0; i < my_size; i++)
				array[i] = val;
			//memset(array, val, capacity * sizeof(T));

		}

		// Copy constructor
		Vector<T>(const Vector<T> &v) 
			: my_size(v.size()), my_capacity(v.capacity()), array( new T[my_capacity])
		{
			for(size_t i = 0; i < my_size; i++)
				array[i] = v[i];
			//memcpy(array, v.array, capacity * sizeof(T));
		}


		~Vector<T>() 
		{ 
			delete [] array;
		}

		
		const T& operator[](size_t index) const 
		{
		    if(index >= my_size || index < 0)
				throw std::out_of_range ("Trying to access index out of range");    	
		    return array[index];
		}

		
		T& operator[](size_t index) 
		{
		    if(index >= my_size || index < 0)
		    	throw std::out_of_range ("Trying to access index out of range");
		    	
		    return array[index];
		}

		
		Vector<T>& operator=(const Vector<T> &v)
		{
			if(this == &v) 
				return *this;
			
			my_size = v.size();
			my_capacity = v.capacity();
			array = new T[my_capacity];
			
			for(size_t i = 0; i < my_size; i++)
				*(array + i) = v[i];
						
			return *this;
		}

		T push_back(T elem)
		{
			// Check if enough capacity
			if(my_size == my_capacity) 
				resize();
			
			array[my_size++] = elem; 
		}

		Vector<T>& insert(size_t index, T elem) 
		{
			if(index < 0)
				throw std::out_of_range("Trying to access index out of range");
			
			if(index >= my_size) {
				push_back(elem);
			} else {
				if(my_size == my_capacity)
					resize();
				
				//Copy everything from i to i+1 (zero or one index??)
				// shift all the elements to the right, right by one
				size_t j = size()-1;
				while(true) {
					T tmp = array[j];
					array[j+1] = tmp;
					if(j == index)
						break;
					j--;
				}
				array[index] = elem;
				my_size++;
			}
			return *this;
		}

		Vector<T>& erase(size_t index) 
		{
			if(index >= my_size || index < 0) {
				throw std::out_of_range("Out or range!");
			}
			if(my_size == 1) {
				return clear();
			}
			if (index < size()-1) {
				// shift all the elements to the right, left by one
				for (size_t i = index+1; i < size(); i++) {
					T tmp = array[i];
					array[i-1] = tmp;
				}
			}
			
			my_size--;
			//array[my_size] = 0;
			return *this;
		}

		Vector<T>& clear() 
		{ 
			my_size = 0;
			return *this;
		}

		
		size_t size() const
		{ 
			return my_size;
		}

		size_t capacity() const
		{
			return my_capacity;
		}

		Vector<T>& sort(bool ascending=true) 
		{
			if (ascending) {
				std::sort(array,array+my_size);
			} else {
				std::sort(std::reverse_iterator<T*>(array+my_size),std::reverse_iterator<T*>(array));
			}
			return *this;	
		}
};