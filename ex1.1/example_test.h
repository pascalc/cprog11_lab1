#ifndef MATRIX_TEST_H_INCLUDED
#define MATRIX_TEST_H_INCLUDED

#include "Matrix.h"
#include "../../cxxtest/cxxtest/TestSuite.h"
#include <fstream>
#include <sstream>

class MatrixTestSuite : public CxxTest::TestSuite
{

    Matrix a_matrix_3by2() {    // [ 1 3 5 ]
        Matrix m;               // [ 0 2 0 ]
        std::stringstream s("  [ 1 3 5 ; 0 2 0 ]");
        s >> m;
        return m;
    }

    Matrix a_matrix_2by3() {    // [ 1 3 ]
        Matrix m;               // [ 5 0 ]
                                // [ 2 0 ]
        std::stringstream s("  [ 1 3; 5 0; 2 0 ]");
        s >> m;
        return m;
    }

    void init_matrix( Matrix& m, const char* file )
    {
        std::stringstream stream( file );   
        stream >> m;
    }

public:
    void testIndexOperator ( )
    {
        Matrix m( 2, 2 );
        TS_ASSERT( m[ 0 ][ 1 ] == 0 );

        m = a_matrix_3by2();
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );

        init_matrix(m, "  [ 1 3 5 ; 0 2 1 ]");
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );

        std::stringstream ss;
        ss << m;
        ss >> m;
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );
    }

    void testAddAndSub() {

    }

    void testMtrxMult() {
        // Correct multiplication 
        Matrix A, B, res(2,2);
        // [ 26 10 ]
        // [ 3 0 ]

        A = a_matrix_3by2();
        B = a_matrix_2by3();
        Matrix C(A*B);
    }

    void testScalarMult() {
        Matrix A(3);
        int k = 4;
        Matrix ans(k*A);
        TS_ASSERT(ans[0][0] == k && ans[1][1] == k && ans[2][2] == k); 
    }
};

#endif

