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


#include "intstring.hpp"
#include <iostream>

int main()
{
    IntString is1{42};
    IntString is2;
    std::cout << "is1 and is2 before move:\n";
    is1.dump();
    is2.dump();

    is2 = std::move(is1); // 移动的一致性会破坏成员的不变量

    std::cout << "is1 and is2 after move:\n";
    is1.dump();
    is2.dump();
}
