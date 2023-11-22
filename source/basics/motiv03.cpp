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


#include <string>
#include <vector>

// Base Cxx03
std::vector<std::string> createAndInsert()
{
    std::vector<std::string> coll; // create vector of strings
    coll.reserve(3); // reserve memory for 3 elements
    const std::string s = "data"; // create string object

    coll.push_back(s); // insert string object
    coll.push_back(s + s); // insert temporary string
    coll.push_back(s); // insert string

    return coll; // return vector of strings
}

int main()
{
    std::vector<std::string> v; // create empty vector of strings
    //...
    v = createAndInsert(); // assign returned vector of strings
    //...
}
