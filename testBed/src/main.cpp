#include <iostream>

class Base
{
public:
    Base() { std::cout << "Constructing Base Class!\n"; }

    virtual void print() { std::cout << "Printing from Base Class!\n"; }
};

class Child : public Base
{
public:
    Child() { std::cout << "Constructing Child Class!\n"; }

    virtual void print() override { std::cout << "Printing from Child Class!\n"; }
};

int main()
{
    std::cout << "Hello World!" << std::endl;
    Child child;
    Base* p_base = &child;
    p_base->print();
}