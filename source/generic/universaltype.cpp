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
#include <string>
#include <string_view>
#include <concepts>

// require a universal reference of a specific type:
// - no implicit type conversions supported
template<typename T>
requires std::same_as<std::remove_cvref_t<T>, std::string>
void requireSame(T&&) {
  //...
}

// require a universal reference of a specific type:
// - implicit but no explicit type conversions supported
template<std::convertible_to<std::string> T>
void requireConvertible(T&&) {
  //...
}

// require a universal reference of a specific type:
// - even explicit type conversions supported
// note: the order of arguments differs
template<typename T>
requires std::constructible_from<std::string, T>
void requireConstructible(T&&) {
  //...
}


int main()
{
  std::string s = "hi";
  std::string_view sv = "hi";
  
  requireSame(s);              // OK
  //requireSame(sv);           // ERROR: no std::string
  //requireSame("hi");         // ERROR: no std::string

  requireConvertible(s);       // OK
  //requireConvertible(sv);    // ERROR: not implicit conversion to std::string
  requireConvertible("hi");    // OK
  
  requireConstructible(s);     // OK
  requireConstructible(sv);    // OK (explicit conversion used)
  requireConstructible("hi");  // OK
}

