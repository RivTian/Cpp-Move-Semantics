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

class Person {
 private:
  std::string first;  // first name
  std::string last;   // last name
 public:
  Person(const std::string& f, const std::string& l)
   : first{f}, last{l} {
  }
  //...
};

