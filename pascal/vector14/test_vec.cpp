#include <iostream>
#include <stdexcept>
#include <cxxtest/TestSuite.h>
#include "vector.h"     // inkludera din headerfil h�r

using namespace std;

class MyTestSuite : public CxxTest::TestSuite {
public:
    
    
    // Testcase 1

    // N�gra saker som ska fungera:


    void test_constructorOneArgument( void ) {
        Vector a(7);           // initiering med 7 element
        Vector b(a);           // kopieringskonstruktor 
        Vector c = a;          // kopieringskonstruktor

        TS_ASSERT_EQUALS(a.size(), 7);
    }

    void test_copyConstructorArgument(void) {
        
        TS_ASSERT_EQUALS(b.size(), 7);    
    
    }
    
    void copyConstructorAssignment(void) {
        TS_ASSERT_EQUALS(c.size(), 7);
    }

    void copyThroughAssignment(void) {
        a = b;             // tilldelning genom kopiering
        TS_ASSERT_EQUALS(a.size(), b.size());
    }

    void assignElement(void) {
        a[5] = 7;              // tilldelning till element
        TS_ASSERT_EQUALS(a[5] == 7);
    }

    const Vector e(10);    // konstant objekt med 10 element
    int i = e[5];          // const int oper[](int) const k�rs
    void randomTest(void) {
        
        TS_ASSERT_EQUALS(e.size(), 10);
        TS_ASSERT_EQUALS(i == 0);
        i = a[0];              // vektorn �r nollindexerad
        TS_ASSERT_EQUALS(i == 0);
        i = a[5];              // int oper[](int) k�rs
        TS_ASSERT_EQUALS(i == 7);
        a[5]++;                // �ka v�rdet till 8
        TS_ASSERT_EQUALS(a[5] == 8);
    }

    void indexOutOfRange(void) {
        try {
        i = e[10];             // f�rs�ker h�mta element som ligger utanf�r e
        } catch (std::out_of_range e) {
            std::cout << e.what() << std::endl;
        }    
    }

    #if 0
    // Diverse saker att testa
    e[5] = 3;              // fel: (kompilerar ej) tilldelning till const
    b = b;                 // hmm: se till att inte minnet som skall beh�llas frig�rs
    #endif  
};   
