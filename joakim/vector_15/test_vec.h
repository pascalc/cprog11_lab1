#include <iostream>
#include <stdexcept>
#include <cxxtest/TestSuite.h>
#include "vector.h"     // inkludera din headerfil här

class MyTestSuite : public CxxTest::TestSuite 
{
public:
    void testInitiateValueConstructor( void ) 
    {
        Vector<int> a(7, 7);           // initiering med 7 element
        TS_ASSERT_EQUALS(a.size(), 7);
        for(size_t i = 0; i < a.size(); i++)
            TS_ASSERT_EQUALS(a[i], 7);
    }

    void testInsertion( void ) {
        cout << "\ntestInsertion" << endl;
        Vector<double> d(10);
        try {
            TS_ASSERT_EQUALS(d.size(), 10);
            d.push_back(3.14);
            TS_ASSERT_EQUALS(d[10], 3.14);
            TS_ASSERT_EQUALS(d.size(), 11);
            } catch (std::out_of_range e) {
                cout << e.what() << endl;
            }
        try {
            d.insert(5, 2.78);
            TS_ASSERT_EQUALS(d[5], 2.78);
        } catch(std::out_of_range e) {
            
        }
        TS_ASSERT_EQUALS(d.size(), 12);
        try {

            TS_ASSERT_EQUALS(d[5], 2.78);
        } catch(std::out_of_range e) {
            
        }
        d.clear();
        TS_ASSERT_EQUALS(d.size(), 0);
    }

    void testPushBack( void ) {
        cout << "testPushBack\n";
        Vector<double> d;
        //cout << "push_back(3.14)\n";
        d.push_back(3.14);
        TS_ASSERT_EQUALS(d.size(), 1);
        TS_ASSERT_EQUALS(d[0], 3.14);
        //cout << "push_back(2.78)\n";
        d.push_back(2.78);
        TS_ASSERT_EQUALS(d.size(), 2);
        TS_ASSERT_EQUALS(d[1], 2.78);
        //cout << "push_back(4711)\n";
        d.push_back(4711);
        TS_ASSERT_EQUALS(d.size(), 3);
        TS_ASSERT_EQUALS(d[2], 4711);
        d.push_back(666.6);
        TS_ASSERT_EQUALS(d.size(), 4);
        TS_ASSERT_EQUALS(d[3], 666.6);
    }

    void testInsert( void ) {
        cout << "\ntestInsert\n";
        Vector<int> ivec;
        try 
        {
            for(int i = 0; i < 10; i++)
                ivec.insert(9-i, i);
        } catch (std::out_of_range e) {
            cout << e.what() << endl;
        }
        cout << "[";
        try {
            for(size_t i = 0; i < ivec.size(); i++) {
                //cout << ivec[i] << ", ";
                TS_ASSERT_EQUALS(ivec[i], 9-i)
            }
        } catch (std::out_of_range e) {
            cout << e.what() << endl;
        }
        cout << "]" << endl;
    }

    void testErase( void ) {
        Vector<char> c;

        TS_ASSERT_EQUALS(c.size(), 0);
        c.insert(0, 'a');
        TS_ASSERT_EQUALS(c.size(), 1);
        c.insert(0, 'b');
        TS_ASSERT_EQUALS(c.size(), 2);
        TS_ASSERT_EQUALS(c[0], 'b');
        TS_ASSERT_EQUALS(c[1], 'a');

        try {
            c.erase(0);
            //TS_ASSERT_EQUALS(c[0], 'a');
        } catch(std::out_of_range e) {
                cout << e.what() << endl;
        }

        TS_ASSERT_EQUALS(c.size(), 1);
        
        // try {
        //     TS_ASSERT_EQUALS(c[0], 'a');
        // } catch(std::out_of_range e) {
        //         cout << e.what() << endl;
        // }
    }

    void testNonConstAssignment( void ) {
        Vector<long> a(7);
        a[5] = 7;            
        int i = a[5];
        a[5]++;
        TS_ASSERT_EQUALS(a[5], 8);
        TS_ASSERT_EQUALS(i , 7);

        a[4] = i;
        TS_ASSERT_EQUALS(a[4], 7);
        i--;
        TS_ASSERT_EQUALS(a[4], 7);

    }

    void testConst( void ) {
        const Vector<int> e(7);
        int i = e[5];
        //e[4] = i;   // Compile error = YES
        i++;
        TS_ASSERT_EQUALS(i, 1);
    }

    void testSelfAssignment( void ) {
        Vector<char> b;
        b = b;
        // How to test? valgrind?
    }

    void testExceptionOutOfRange( void ) {
        // How to test?
    }
};
