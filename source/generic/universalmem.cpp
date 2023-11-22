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
#include <vector>

template<typename T>
void insert(T& coll, typename T::value_type&& arg) 
{
  coll.push_back(arg);
}

int main()
{
  std::vector<std::string> coll;
  //... 
  insert(coll, std::string{"prvalue"});  // OK
  //...
  std::string str{"lvalue"};
  insert(coll, str);              // ERROR: T::value_type&& is not a universal reference
  insert(coll, std::move(str));   // OK
  //... 
}

