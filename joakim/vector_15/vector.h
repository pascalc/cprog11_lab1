template<class T>
class Vector {
	public:
		// Constructors
		Vector();
		explicit Vector(size_t size);
		explicit Vector(size_t size, const T &val);
		explicit Vector(const Vector<T> &v);
		// Deconstructor
		~Vector();

		// Functions
		const T operator[](unsigned int i) const throw (std::out_of_range);
		T& operator[](unsigned int i) throw (std::out_of_range);
		Vector& operator=(const Vector<T> &vector);
		void push_back(const T &elem);	// Add element elem last in the vector
		void insert(size_t i, const T &elem);	// Insert element elem before index i	
		void erase(size_t i);	// Erase element at index i 
		void clear();	// Remove ALL elements in the vector
		// Should be const!
		size_t size();	// Return number of elements in the vector.
		void sort(bool ascending = true); // Sort in asc/desc order. Default is asc
		void resize();	// Change capacity to meet requirments
		
	private:
		// Variables
		unsigned int capacity;	// capacity of the vector. size * sizeof(T)
		unsigned int size;		// size of the vector
		T* array;				// underlaying array of type T (generic)

		// ?? const unsigned int ELEM_SIZE = sizeof(T);

		// Functions
		
		/* 	Set all the values in an array to zero
		 	arg: starting point of a array a 
		*/
		void initiate(T * array, const T &val = T());
};