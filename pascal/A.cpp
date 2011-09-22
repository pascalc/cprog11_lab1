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
    std::cout << "Some other constructor" << std::endl;
    A a("my name is a");
    std::cout << "1. A b = a <-- copy constructor" << std::endl;
    A b = a;         // vad är skillnaden
    std::cout << "2. A c(a) <--> A c = a <-- copy constructor" << std::endl;
    A c(a);          // mellan dessa
    std::cout << "3. A d; d = a <-- assignment operator" << std::endl;
    A d;             // tre tekniker?
    d = a;

    std::cout << "noref(a) <-- send by value, so temp object created and destroyed" << std::endl;
    no_ref(a);       // Bildas temporära objekt?
    std::cout << "with_ref(a) <-- send by ref so no temp object" << std::endl;
    with_ref(a);     // Bildas temporära objekt?

    std::cout << "Array creation <-- default constructor * 5" << std::endl;
    A *aa = new A[5];
    std::cout << "delete aa <-- not array delete, so only first A deleted, MEMORY LEAK" << std::endl;
    delete aa;       // Vad kommer att hända?
    std::cout << "end main" << std::endl;
    return 0;
}
