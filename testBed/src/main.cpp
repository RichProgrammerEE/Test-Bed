#include <iostream>
#include <vector>
#include <thread>

using namespace std;

class OwnedObject
{
public:
    OwnedObject(const std::string& message) :
    _message(message)
    {
        std::cout << "Constructing OwnedObject class, message(" << message << ")\n";
    }

    ~OwnedObject()
    {
        std::cout << "Deconstructing OwnedObject class, message(" << _message << ")\n";
    }
private:
    std::string _message;
};

class Parent
{
public:
    Parent() :
    _ownedObj("Parent Class")
    {
        std::cout << "Constructing Parent class\n";
    }

    ~Parent()
    {
       std::cout << "Deconstructing Parent class\n"; 
    }

    virtual void print()
    {
        std::cout << "Printing from Parent class\n";
    }
private:
    OwnedObject _ownedObj;
};

class Child : public Parent
{
public:
    Child() :
    Parent(),
    _ownedObj("Child Class")
    {
        std::cout << "Constructing Child class\n";
    }

    ~Child()
    {
       std::cout << "Deconstructing Child class\n"; 
    }

    virtual void print() override
    {
        std::cout << "Printing from Child class\n";
    }
private:
    OwnedObject _ownedObj;
};

int main()
{
    auto c = Child();
    return 0;
}