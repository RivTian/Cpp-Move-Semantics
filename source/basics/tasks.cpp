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


#include "tasks.hpp"
#include <iostream>
#include <chrono>

int main()
{
    Tasks ts;
    ts.start([]
    {
        std::this_thread::sleep_for(std::chrono::seconds{2});
        std::cout << "\nt1 done" << std::endl;
    });
    ts.start([]
    {
        std::cout << "\nt2 done" << std::endl;
    });
}
