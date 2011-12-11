#include <iostream>
#include <stdlib.h>

using namespace std;

class A {
public:
    A() 
        {std::cout << "The default contructor" << std::endl; }
    A(const A & ref) 
        {std::cout << "The copy contructor" << std::endl; }
    ~A() 
        {std::cout << "The destructor" << std::endl; }
    A(char * s) 
        {std::cout << "Some other constructor " << s << std::endl;}
    A & operator=(const A & s) 
        {std::cout << "The assignment operator" << std::endl; 
         return *this;}
};

void no_ref(A a) {
    cout << "no_ref(A a) {}, &a = " << &a << endl; 
}
void with_ref(const A & a) {
    cout << "with_ref(const A &a) {}, &a = " << &a << endl;
}

int main()
{
    A a("my name is a");
    cout << "A a('my name is a'); " << &a << endl << endl;
    A b = a;         // vad är skillnaden
    cout << "A b = a; " << &b << endl << endl;
    A c(a);          // mellan dessa
    cout << "A c(a): " << &c << endl << endl;
    A d;             // tre tekniker?
    cout << "A d; " << &d << endl<< endl;
    d = a;
    cout << "d = a; " << &d << endl << endl;

    no_ref(a);       // Bildas temporära objekt?
    with_ref(a);     // Bildas temporära objekt?

    A *aa = new A[5];

    delete aa;       // Vad kommer att hända?
    return 0;
}
