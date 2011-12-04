#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

class Matrix {
public:
    typedef unsigned int index;

    class matrix_row : private Vector< int > {
        public:
            matrix_row( std::size_t s = 0) : Vector< int >( s ) {}
            using Vector<int>::operator [];
        private:
            friend std::istream& operator>>( std::istream&, Matrix& );
    };
    
    Matrix( );
    Matrix( std::size_t, std::size_t );
    Matrix( const Matrix& );
    Matrix(std::size_t size);   // changed from int to std::size_t
    ~Matrix( );

    friend std::ostream& operator<<(std::ostream&, const Matrix&);
    
    Matrix& operator= ( const Matrix& );
    Matrix operator+ ( const Matrix& ) const; 
    Matrix operator* ( const Matrix& ) const; 
    Matrix operator* ( int ) const;
    Matrix operator-( const Matrix& ) const; 
    Matrix operator-( ) const;
    
    Matrix& transpose( );
    
    matrix_row& operator[]( index i );
    const matrix_row& operator[]( index i ) const;
    
    inline std::size_t rows() { return m_rows; } const;
    inline std::size_t cols() { return m_cols; } const;
    
 protected:
 private:
    Vector< matrix_row >        m_vectors;
    std::size_t                 m_rows;
    std::size_t                 m_cols;
    
    bool validate(const Matrix&) const;
    int add(int, int) const;
    int sub(int, int) const;
    Matrix m_iterator(const Matrix&, (int)(Matrix::operator*)(int, int));
    Matrix m_iterator(const Matrix&, int);


    friend std::istream& operator>> ( std::istream&, const Matrix& );
};

std::istream& operator>> ( std::istream&, const Matrix& );
std::ostream& operator<< ( std::ostream&, Matrix& );
Matrix operator* ( int, const Matrix& );

#endif // MATRIX_H