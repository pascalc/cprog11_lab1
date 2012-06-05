//hypercube.cpp
#include "hypercube.h"

#include <iostream>

Hypercube<N>::Hypercube<std::size_t size) : 
	vector_(size, Hypercube<N-1>(size))
{

}

const Hypercube<N-1>& Hypercube<N>::operator[](unsigned int i) const 
{ 
	return vector_[i]; 
}

Hypercube<N-1>& Hypercube<N>::operator[](unsigned int i) 
{ 
	return vector_[i];	
}

Hypercube<1>::Hypercube(std::size_t size) :	
	vector_(size, int)
{

}

const int& Hypercube<1>::operator[](unsigned int i) const 
{ 
	return vector_[i]; 
}

int& Hypercube<1>::operator[](unsigned int i) 
{ 
	return vector_[i]; 
}