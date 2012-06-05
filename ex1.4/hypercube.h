// hypercube.h
#include <iostream>
#include <vector>

template<int N>
class Hypercube {
	public:
		explicit Hypercube(std::size_t size) : vector_(size, Hypercube<N-1>(size)) {}
		const Hypercube<(N-1)>& operator[](unsigned int i) const { return vector_[i]; }
		Hypercube<(N-1)>& operator[](unsigned int i) { return vector_[i]; }
	private:
		std::vector< Hypercube<N-1> > vector_;
};

template<>
class Hypercube<1> {
	public:
		explicit Hypercube(std::size_t size) : vector_(size) {}
		const int& operator[](unsigned int i ) const { return vector_[i]; }
		int& operator[](unsigned int i) { return vector_[i]; }
	private:
		std::vector<int> vector_;
};