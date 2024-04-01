#include <iostream>

/*Primer za rabota s explicit 
class MyClass {
public:
    explicit MyClass(int x) : value(x) {}
    int getValue() const { return value; }
private:
    int value;
};

int main() {
     MyClass obj(5); // Raboti pravilno vinagi
    //MyClass obj = 5; // bez explicit raboti, zahtoto neqvno konvertira int da bude obekt, s explicit nqma da mu pozvoli
    std::cout << "Value: " << obj.getValue() << std::endl;

    return 0;
}*/

/*Zad 1*/
int main()
{
    class A {
    public:
        void f() const
        {
            g();
        }
        void g() const {}
    };
}

