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
#include <type_traits>

class B
{
    std::string s;
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << std::is_nothrow_default_constructible<B>::value << '\n';
    std::cout << std::is_nothrow_copy_constructible<B>::value << '\n';
    std::cout << std::is_nothrow_move_constructible<B>::value << '\n';
    std::cout << std::is_nothrow_copy_assignable<B>::value << '\n';
    std::cout << std::is_nothrow_move_assignable<B>::value << '\n';
}
