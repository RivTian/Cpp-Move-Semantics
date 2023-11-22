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

#pragma once
#include <string>
#include <iostream>

class Person
{
private:
    std::string name;

public:
    Person(const char* n)
        : name{n}
    {
    }

    std::string getName() const
    {
        return name;
    }

    // print out when we copy:
    Person(const Person& p)
        : name{p.name}
    {
        std::cout << "COPY " << name << '\n';
    }

    // force default generated move constructor:
    Person(Person&& p) = default;
    //...
};
