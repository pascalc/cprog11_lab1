#include "oMatrix.h"

#include <iostream>
#include <algorithm>
#include <stdexcept>

Matrix::Matrix() : 
	m_vectors(0), 
	m_rows(0), 
	m_cols(0) {}

Matrix::Matrix(std::size_t nr_rows, std::size_t nr_cols) : 
	m_vectors(nr_cols, matrix_row(nr_rows)),
	m_rows(nr_rows),
	m_cols(nr_cols) {}

Matrix::Matrix(std::size_t size ) : 
    m_vectors(size, matrix_row(size)),
    m_rows(size),
    m_cols(size) 
{
    for(size_t row = 0; row < m_rows; ++row)
            m_vectors[row][row] = 1;
}

Matrix::Matrix(const Matrix& matrix) : 
    m_vector(matrix.cols(), matrix_row(matrix.rows())),
    m_rows(matrix.m_rows),
    m_cols(matrix.m_cols) 
{
    std::copy(m_vectors.begin(), m_vectors.end(), std::back_inserter(matrix.m_vectors) );        
}

Matrix::~Matrix() { } // deallocation of memory is handled (supported) via Vector

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)  {
    os << "[";
    for(size_t row = 0; row < m_rows; ++row) {
        for(size_t col = 0; col < m_cols; ++col) {
            if(row != 0 && col == m_cols - 1)
                os << " " << matrix[col][row];
        }
        os << "\n;";
    }
    os << " ]";
    return os;
}

// TODO
std::istream& operator<<(std::istream& os, const Matrix& matrix) {
    
}

Matrix& Matrix::operator=(const Matrix& matrix) {
    if(*this != matrix) {
        m_rows = matrix.rows();
        m_cols = matrix.cols();
        m_vectors.clear();

        std::copy(m_vectors.begin(), m_vectors.end(), std::back_inserter(matrix.m_vectors) );
    }
    return *this;
}

/*****/
inline void Matrix::validate(const Matrix& m) const { 
    if(m.rows() != m_rows || m.cols() != m_cols)
        throw std::log_error("Matrix dimensions must agree");
}

inline int Matrix::add(int a, int b) const { return a+b; }
inline int Matrix::sub(int a, int b) const { return a-b; }

Matrix Matrix::m_iterator(const Matrix& m, (int)(Matrix::operator*)(int, int)) {
    validate(m);
        
    Matrix ret(*this);
    for(size_t row = 0; row < m_rows; ++row)
        for(size_t col = 0; col < m_cols; ++col)
            ret[col][row] = (*this).operator(ret[col][row], m[col][row]);

    return ret;
}

Matrix Matrix::m_iterator(const Matrix& m, int k) {
    validate(m);
    
    Matrix ret(*this);
    for(size_t row = 0; row < m_rows; ++row)
        for(size_t col = 0; col < m_cols; ++col)
            ret[col][row] *= k;

    return ret;
}
/*****/

Matrix Matrix::operator+(const Matrix& matrix) const { 
    return m_iterator(matrix, &add);
}

Matrix Matrix::operator-(const Matrix& matrix) const {
    return m_iterator(matrix, &sub);
}

Matrix Matrix::operator*(int k) const {
    return m_iterator(*this, k);
}

Matrix Matrix::operator-() const {
    return m_iterator(*this, -1);
}

Matrix Matrix::operator*(const Matrix& matrix) const {
    size_t _rows = matrix.rows();
    size_t _cols = matrix.cols();

    if(m_cols != _rows)
        throw std::logic_error("Matrix dimensions must agree");
    
    Matrix res(m_rows, _cols);
    
    for(size_t row = 0; row < m_rows; ++row) {
        for(size_t col = 0; col < _cols; ++col) {
            int cell_value = 0;
            for(size_t i = 0; i < _rows; ++i)
                cell_value += (*this)[_col][i]*matrix[i][_row];
            ret[col][row] = cell_value;
        }
    }
    return res;
}

Matrix& Matrix::transpose() {
    int _rows = m_cols;
    int _cols = m_rows;
    Matrix _vectors(_cols, _rows);

    for(size_t row = 0; row < m_rows; ++row)
        for(size_t col = 0; col < m_cols; ++col)
            _vectors[col][row] = (*this)[row][col];
    
    int m_cols = _rows;
    int m_rows = _cols;
    m_vectors = _vectors;
    _vectors.clear(); // deallocate memory

    return *this;
}

matrix_row& Matrix::operator[](index i) {
    return (*this)[i];
}

const matrix_row& Matrix::operator[](index i) const {
    return (*this)[i];
}

Matrix operator*(int k, const Matrix& matrix) {
    return k * matrix;
}