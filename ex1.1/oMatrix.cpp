#include "oMatrix.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <string>

Matrix::Matrix() : 
	m_vectors(0), 
	m_rows(0), 
	m_cols(0) {}

Matrix::Matrix(std::size_t nr_rows, std::size_t nr_cols) : 
	m_vectors(nr_rows, matrix_row(nr_cols)),
	m_rows(nr_rows),
	m_cols(nr_cols) {}

Matrix::Matrix(std::size_t size ) : 
    m_vectors(size, matrix_row(size)),
    m_rows(size),
    m_cols(size) 
{
    for(size_t i = 0; i < m_rows; ++i)
            (*this)[i][i] = 1;
}

Matrix::Matrix(const Matrix& m) : 
    m_vectors(m.rows(), matrix_row(m.cols())),
    m_rows(m.m_rows),
    m_cols(m.m_cols) 
{
    //typedef Vector< matrix_row >::const_iterator it; // TODO
    //std::copy(it.begin(), m.m_vectors.end(), std::back_inserter(m.m_vectors) );
    for(size_t r = 0; r < m_rows; ++r)
        for(size_t c = 0; c < m_cols; ++c)
            (*this)[r][c] = m[r][c];
}

Matrix::~Matrix() { } // deallocation of memory is handled (supported) via Vector

Matrix& Matrix::operator=(const Matrix& m) {
    if(this != &m) {
        m_rows = m.rows();
        m_cols = m.cols();
        m_vectors.clear();
        Vector<Matrix::matrix_row> m_vectors(m_cols, m_rows);
        // TODO
        //std::copy(m_vectors.begin(), m_vectors.end(), std::back_inserter(m.m_vectors) );
        for(size_t r = 0; r < m_rows; ++r)
            for(size_t c = 0; c < m_cols; ++c)
                (*this)[r][c] = m[r][c];
    }
    return *this;
}

void Matrix::validate(const Matrix& m) const { 
    if(m.rows() != m_rows || m.cols() != m_cols)
        throw std::logic_error("Matrix dimensions must agree");
}

int Matrix::add(int a, int b) const { return a+b; }
int Matrix::sub(int a, int b) const { return a-b; }

Matrix Matrix::m_iterator(const Matrix& m, int (*ptr2operator)(int, int) ) {
    validate(m);
    
    Matrix res(*this);
    for(size_t row = 0; row < m.rows(); ++row)
        for(size_t col = 0; col < m.cols(); ++col)
            res[row][col] = ptr2operator(res[row][col], m[row][col]);

    return res;
}

Matrix Matrix::operator+(const Matrix& m) const { 
    //return m_iterator(m, &add);
    validate(m);
    Matrix res(*this);
    for(size_t r = 0; r < m_rows; ++r)
        for(size_t c = 0; c < m_cols; ++c)
            res[r][c] += (*this)[r][c];
}

Matrix Matrix::operator-(const Matrix& m) const {
    //return m_iterator(m, &sub);
    validate(m);
    Matrix res(*this);
    for(size_t r = 0; r < m_rows; ++r)
        for(size_t c = 0; c < m_cols; ++c)
            res[r][c] -= (*this)[r][c];
}

Matrix Matrix::operator*(int k) const {
    //return m_iterator((*this), k);
    Matrix res(*this);
    for(size_t r = 0; r < m_rows; ++r)
        for(size_t c = 0; c < m_cols; ++c)
            res[r][c] *= k;;
}

Matrix Matrix::operator-() const {
    return (*this)*(-1);

}

Matrix Matrix::operator*(const Matrix& m) const {
    size_t rhs_rows = m.rows();
    size_t rhs_cols = m.cols();

    if(m_cols != rhs_rows)
        throw std::logic_error("Matrix dimensions must agree");
    
    Matrix res(m_rows, rhs_cols);
    
    for(size_t row = 0; row < m_rows; ++row) {
        for(size_t col = 0; col < rhs_cols; ++col) {
            int cell_value = 0;
            for(size_t i = 0; i < rhs_rows; ++i)
                cell_value += (*this)[i][col]*m[row][i];
            res[row][col] = cell_value;
        }
    }
    return res;
}

Matrix& Matrix::transpose() {
    Matrix copy(*this);

    int new_rows = m_cols;
    int new_cols = m_rows;
    m_vectors.clear();
    Vector<Matrix::matrix_row> m_vectors(m_cols, m_rows);

    for(size_t row = 0; row < new_rows; ++row)
        for(size_t col = 0; col < new_cols; ++col)
            (*this)[row][col] = copy[col][row];
    
    int m_rows = new_rows;
    int m_cols = new_cols;

    return *this;
}

Matrix::matrix_row& Matrix::operator[](index i) {
    return (*this)[i];
}

const Matrix::matrix_row& Matrix::operator[](index i) const {
    return (*this)[i];
}

Matrix operator*(int k, const Matrix& m) {
    return k * m;
}

inline std::size_t Matrix::rows() const { 
    return m_rows; 
}

inline std::size_t Matrix::cols() const { 
    return m_cols; 
}

// Output
std::ostream& operator<<(std::ostream& os, const Matrix& m)  {
    size_t rows = m.rows(), cols = m.cols();
    os << "[";
    for(size_t row = 0; row < rows; ++row) {
        for(size_t col = 0; col < cols; ++col) {
            os << " " << m[row][col];
        }
        if(row != rows-1)
            os << "\n;";
    }
    os << " ]";
    return os;
}

// TODO
// Input. 3x3 matrix = [1 2 3; 4 5 6; 7 8 9]
std::istream& operator>>(std::istream& is, Matrix& m) {
    if(is.get() != ']') throw std::invalid_argument("Invalid input. Expected ']'");

    size_t rows = 0, cols = 0;
    std::string input, row;
    std::getline(is, input);

    std::istringstream line(input);
    while(std::getline(line, row, ';')) {
        Matrix::matrix_row m_row;
        std::copy(std::istream_iterator<int>(row), std::istream_iterator<int>(),
                std::back_inserter(m_row));
        ++rows;
        cols = m_row.size();
        m.m_vectors.push_back(m_row);
        m_row.clear();
    }
    if(rows == 0) m = Matrix();
    m.m_rows = rows;
    m.m_cols = cols;
    return is;
}

// Obsolete
Matrix::Matrix(int size) : 
    m_vectors(size, matrix_row(size)),
    m_rows(size),
    m_cols(size) 
{
    for(int i = 0; i < m_rows; ++i)
            (*this)[i][i] = 1;
}