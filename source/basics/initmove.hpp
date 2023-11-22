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
public:
    Person(std::string&& f, std::string&& l)
        : first{std::move(f)}, last{std::move(l)}
    {
        std::cout << "Person(std::string&&, std::string&&)" << std::endl;
        std::cout << first << " " << last << std::endl;
    }

    //...

public:
    std::string first; // first name
    std::string last; // last name
};
