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

class X {
 public:
  X() = default;

  X(const X&) {
    std::cout << "copy constructor\n";
  }
  X(X&&) {
    std::cout << "move constructor\n";
  }

  template<typename T>
  X(T&&) {
    std::cout << "universal constructor\n";
  }  
};

int main()
{
  X xv;
  const X xc;

  X xcc{xc};             // OK: calls copy constructor
  X xvc{xv};             // OOPS: calls universal constructor
  X xvm{std::move(xv)};  // OK: calls move constructor
  X xcm{std::move(xc)};  // OOPS: calls universal constructor
}

