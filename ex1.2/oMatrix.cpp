#include "oMatrix.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <iterator>
#include <cctype>

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
    for(size_t i = 0; i < size; ++i)
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
/*
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
*/

Matrix Matrix::operator+(const Matrix& m) const { 
    //return m_iterator(m, &add);
    validate(m);
    Matrix res(*this);
	for(size_t r = 0; r < m_rows; ++r) {
		for(size_t c = 0; c < m_cols; ++c) {
			res[r][c] += (*this)[r][c];
		}
	}
	return *this;
	
}

Matrix Matrix::operator-(const Matrix& m) const {
    //return m_iterator(m, &sub);
    validate(m);
    Matrix res(*this);
    for(size_t r = 0; r < m_rows; ++r)
        for(size_t c = 0; c < m_cols; ++c)
            res[r][c] -= (*this)[r][c];
	
	return *this;
}

Matrix Matrix::operator*(int k) const {
    //return m_iterator((*this), k);
    Matrix res(*this);
    for(size_t r = 0; r < m_rows; ++r)
        for(size_t c = 0; c < m_cols; ++c)
            res[r][c] *= k;
	
	return *this;
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

    size_t new_rows = m_cols;
    size_t new_cols = m_rows;
    m_vectors.clear();
    Vector<Matrix::matrix_row> m_vectors(m_cols, m_rows);

    for(size_t row = 0; row < new_rows; ++row)
        for(size_t col = 0; col < new_cols; ++col)
            (*this)[row][col] = copy[col][row];
    
    (*this).m_rows = new_rows;
    (*this).m_cols = new_cols;

    return *this;
}

Matrix::matrix_row& Matrix::operator[](index i) {
    return m_vectors[i];
}

const Matrix::matrix_row& Matrix::operator[](index i) const {
    return m_vectors[i];
}

Matrix operator*(int k, const Matrix& m) {
    return k * m;
}

std::size_t Matrix::rows() const { 
    return m_rows; 
}

std::size_t Matrix::cols() const { 
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

void trim_whitespaces(std::istream& is) {
	while( is.good() ) {
		if(! std::isspace( is.get() ) ) {
			// When not space, go to previous character and break
			is.unget();
			return;
		}
	}
}std::istream& operator>>(std::istream& is, Matrix& m)
{
    // Read [
    trim_whitespaces(is);
    if (!is.good() || is.get() != '[') {
        throw std::invalid_argument("does not start with [");
    }
    trim_whitespaces(is);
    
    size_t c = 0, r = 0;; // current column / row
    size_t cols = -1; // number of columns
    Matrix::matrix_row values;
    while (is.good()) {
        int ch = is.get();
        
        // Ignore whitespace
        if (std::isspace(ch)) continue;
        
        if (ch == ';' || ch == ']') {
            // Set / check column count
            if (r == 0 && c == 0 && ch == ']') {
                // Empty matrix
                m = Matrix();
                return is;
            } else if (r == 0) {
                // First row
                cols = c;
                m = Matrix(1, cols);
                m.m_vectors.clear(); // remove zero row
            } else if (c != cols) {
                // Not same length as first row
                throw std::invalid_argument("rows have different lengths");
            } else {
                ++m.m_rows;
            }
            
            // Add this row
            m.m_vectors.push_back(values);
            values.clear();
            c = 0;
            ++r;
            
            if (ch == ']') return is;
            else continue;
        }
        
        // Number
        is.unget();
        int num;
        is >> num;
        values.push_back(num);
        ++c;
    }
    
    throw std::invalid_argument("unexpected end of stream");
}
//~ std::istream& operator>>(std::istream& is, Matrix& m) {
	//~ std::cout << std::endl << "operator>>" << std::endl;
	//~ // trim leading whitespaces (if any)
	//~ trim_whitespaces(is);
	//~ if(is.get() != '[' || !is.good() ) throw std::invalid_argument("Invalid input. Expected '[' as first character");
	//~ trim_whitespaces(is);
	
	//~ size_t rows = 0, cols = 0;
	//~ Matrix::matrix_row row;
	//~ while( is.good() ) {
		//~ int digit = is.get();
		
		//~ std::cout << digit << " ";
		//~ if(! std::isdigit(digit) ) {
			//~ // end of row
			//~ if(digit == ';' ) {
				//~ rows++;
				//~ m.m_vectors.push_back(row);
				//~ row.clear();
			//~ }
			//~ // end of input
			//~ if(digit == ']') {
				//~ if(rows == 0 && cols == 0) {
					//~ m = Matrix();
				//~ }
				//~ return is;
			//~ }
		//~ }
		//~ else {
			//~ row.push_back(digit);
			//~ cols++;
		//~ }
		
		//~ if(!std::isspace( is.get() )) is.unget();
	//~ }
	
	//~ std::invalid_argument("Invalid input. Expected ']' as last character");
//~ }

// Obsolete
Matrix::Matrix(int size) : 
    m_vectors(size, matrix_row(size)),
    m_rows(size),
    m_cols(size) 
{
    for(size_t i = 0; i < m_rows; ++i)
            (*this)[i][i] = 1;
}

std::ostream& operator<<(std::ostream& os, Matrix& m) {
    return os << static_cast<const Matrix&>(m);
}