//********************************************************
// The following code example is taken from the book
//  C++ Move Semantics - The Complete Guide
//  by Nicolai M. Josuttis (www.josuttis.com)
//  http://www.cppmove.com
//
// The code is licensed under a
//  Creative Commons Attribution 4.0 International License
//  http://creativecommons.org/licenses/by/4.0/
//********************************************************


#include <iostream>
#include <string>
#include <vector>

template <typename T>
class Coll
{
private:
    std::vector<T> values;

public:
    Coll() = default;

    // function in class template:
    void insert(T&& val)
    {
        values.push_back(std::move(val));
    }
};

int main()
{
    Coll<std::string> coll;
    //...
    coll.insert(std::string{"prvalue"}); // OK
    std::string str{"lvalue"};
    coll.insert(str); // ERROR: T&& of Coll<T> is not a universal reference
    coll.insert(std::move(str)); // OK
    //...
}
