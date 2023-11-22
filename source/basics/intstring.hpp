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
#include <iostream>
#include <string>

class IntString
{
private:
    int val; // value
    std::string sval; // cached string representation of the value
public:
    IntString(int i = 0)
        : val{i}, sval{std::to_string(i)}
    {
    }

    void setValue(int i)
    {
        val = i;
        sval = std::to_string(i);
    }

    //...
    void dump() const
    {
        std::cout << " [" << val << "/'" << sval << "']\n";
    }
};
