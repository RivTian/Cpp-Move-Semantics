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


#include "personmove.hpp"
#include <iostream>
#include <vector>

int main()
{
    std::vector<Person> coll{
        "Wolfgang Amadeus Mozart",
        "Johann Sebastian Bach",
        "Ludwig van Beethoven"
    };
    std::cout << "capacity: " << coll.capacity() << '\n';
    coll.push_back("Pjotr Iljitsch Tschaikowski");
}
