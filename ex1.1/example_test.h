#ifndef MATRIX_TEST_H_INCLUDED
#define MATRIX_TEST_H_INCLUDED

#include "Matrix.h"
#include "../../cxxtest/cxxtest/TestSuite.h"
#include <fstream>
#include <sstream>

class MatrixTestSuite : public CxxTest::TestSuite
{

    Matrix a_matrix_3by2() {
        return init_matrix("  [ 1 3 5 ; 0 2 0 ]");
    }

    Matrix a_matrix_2by3() {
        return init_matrix("  [ 1 0 ; 3 2 ; 5 0 ]");
    }

    Matrix init_matrix(const char* m_str) {
        Matrix m;
        std::stringstream s(m_str);
        s >> m;
        return m;

    }

    void init_matrix( Matrix& m, const char* file )
    {
        std::stringstream stream( file );   
        stream >> m;
    }

public:
    void test_constructors() {
        // Default constructor
        Matrix a;
        TS_ASSERT(a.rows() == 0 && a.cols() == 0);
        // Explicit constructor
        Matrix b(3);
        TS_ASSERT(b == init_matrix("[ 1 0 0 ; 0 1 0; 0 0 1 ]") );
        Matrix c(1);
        TS_ASSERT(c[0][0] == 1);
        // Constructur two arguments
        Matrix d(3, 2);
        TS_ASSERT(d.rows() == 3 && d.cols() == 2);
        Matrix e(3,3);
        TS_ASSERT(e.rows() == 3 && e.cols() == 3);
    }

    void test_copy() {
        // Copy default vector via assignment operator
        Matrix a;
        Matrix b = a;
        TS_ASSERT(b.rows() == 0 && b.cols() == 0);

        // Copy non-empty vectors via copy constructor and assignment operator
        Matrix c = init_matrix("  [ 1 3 5 ; 0 2 0 ]");
        Matrix d(c);
        TS_ASSERT(d == c);
        Matrix h = d;
        TS_ASSERT(h == d); 
    }

    void test_indexOperator ( ) {
        Matrix m( 2, 2 );
        TS_ASSERT( m[ 0 ][ 1 ] == 0 );

        m = a_matrix_3by2();
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );

        init_matrix(m, "  [ 1 3 5 ; 0 2 1 ]");
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );
        TS_ASSERT(m[2][2] == 1);

        std::stringstream ss;
        ss << m;
        ss >> m;
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );
    }

    void test_setIndexOperator() {
        Matrix a(3);
        for(std::size_t r = 0; r < a.rows(); ++r) {
            for(std::size_t c = 0; c < a.cols(); ++c) {
                a[r][c] = r + c;
                TS_ASSERT(a[r][c] == (r+c) );
            }
        }

        Matrix b(3,2);
        b[0][0] = 1;
        b[0][1] = 2;
        b[1][0] = 3;
        b[1][1] = 4;
        b[2][0] = 5;
        b[2][1] = 6;
        std::size_t i = 1;
        for(std::size_t r = 0; r < b.rows(); ++r) {
            for(std::size_t c = 0; r < b.cols(); ++c) {
                TS_ASSERT(b[r][c] == i++ );
            }
        }
    }

    void test_addition() {
        //Test valid addition
        // Test non-square
        Matrix a = init_matrix("  [ 1 3 5 ; 0 2 0 ]");
        Matrix b = a;
        Matrix c = a + b;
        TS_ASSERT(c[0][0] == 2 && c[0][1] == 6 &&c[0][2] == 10
                    && c[1][0] == 0 && c[1][1] == 4 && c[1][2] == 0);

        // Test square
        char* square = {"[ 1 2 3 ; 0 2 0 ; 0 0 1 ]"};
        char* result = {"[ 2 4 6 ; 0 4 0 ; 0 0 2 ]"};
        Matrix d = init_matrix(square);
        Matrix e = d + d;
        TS_ASSERT(e == init_matrix(result))

        // Test adding matrices with wrong dimensions
        Matrix f(3);
        TS_ASSERT_THROWS_ANYTHING(Matrix e = f + a);
    }

    void test_subtraction() {
        // Test valid subtraction

        // Test non-square
        Matrix a = init_matrix("  [ 1 3 5 ; 0 2 0 ]");
        Matrix b = a;
        Matrix c = a - b;
        TS_ASSERT(c[0][0] == 0 && c[0][1] == 0 &&c[0][2] == 0
                    && c[1][0] == 0 && c[1][1] == 0 && c[1][2] == 0);
        
        // Test square
        char* square = {"[ 1 2 3 ; 0 2 0 ; 0 0 1 ]"};
        char* result = {"[ 0 0 0 ; 0 0 0 ; 0 0 0 ]"};
        Matrix d = init_matrix(square);
        Matrix e = d - d;
        TS_ASSERT(e == init_matrix(result))

        // Test subtracting matrices with wrong dimensions
        Matrix f(3);
        TS_ASSERT_THROWS_ANYTHING(Matrix e = f - a);
    }

    void test_matrixMult() {
        char* result = {" [ 26 10 ; 3 0 ]"};

        // Correct multiplication 
        Matrix a = a_matrix_3by2();
        Matrix b = a_matrix_2by3();
        Matrix c = a*b;
        TS_ASSERT(c == init_matrix(result));
        
        // Wrong dimensions
        Matrix d(3);
        TS_ASSERT_THROWS_ANYTHING(Matrix e = d*b);        
    }

    void test_scalarMultiplication() {
        Matrix a(3);
        // Test left side
        Matrix ans = 4*a;
        TS_ASSERT(ans[0][0] == 4 && ans[0][1] == 0 && ans[0][2] == 0
                    && ans[1][0] == 0 && ans[1][1] == 4 && ans[1][2] == 0
                    && ans[2][0] == 0 && ans[2][1] == 0 && ans[2][2] == 4);
        // Test right side
        a = a_matrix_3by2();
        ans = a*4;
        TS_ASSERT(ans[0][0] == 4 && ans[0][1] == 12 && ans[0][2] == 20
                    && ans[1][0] == 0 && ans[1][1] == 8 && ans[1][2] == 0);
        // Test negative scalar multiplication
        a = a_matrix_2by3();
        ans = -4*a;
        TS_ASSERT(ans[0][0] == -4 && ans[0][1] == -12 
                    && ans[1][0] == -20 && ans[1][1] == 0
                    && ans[2][0] == -8 && ans[2][1] == 0);
    }

    void test_transposeRectangular() {
        Matrix a = a_matrix_3by2();
        Matrix aT = a_matrix_2by3();
        a.transpose();
        TS_ASSERT(a == aT);
    }

    void test_transposeSquare() {
        Matrix a(10);
        a.transpose();
        TS_ASSERT(a == a);
    }

    void test_negation() {
        char* res1 = {"[ -1 0 ; 0 -1]"};
        Matrix a(2);
        TS_ASSERT(-a == init_matrix(res1));
    }

};
#endif

