#include <iostream>

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

void no_ref(A a) {}
void with_ref(const A & a) {}

int main()
{
    std::cout << "My name is a" << std::endl;
    A a("my name is a");
    std::cout << "1." << std::endl;
    A b = a;         // vad är skillnaden
    std::cout << "2." << std::endl;
    A c(a);          // mellan dessa
    std::cout << "3." << std::endl;
    A d;             // tre tekniker?
    d = a;

    std::cout << "noref(a)" << std::endl;
    no_ref(a);       // Bildas temporära objekt?
    std::cout << "noref(b)" << std::endl;
    with_ref(a);     // Bildas temporära objekt?

    std::cout << "Array creation" << std::endl;
    A *aa = new A[5];
    std::cout << "Array deletion" << std::endl;
    delete aa;       // Vad kommer att hända?
    std::cout << "end main" << std::endl;
    return 0;
}
