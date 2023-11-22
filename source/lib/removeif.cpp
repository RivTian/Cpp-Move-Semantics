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


#include "email.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
  std::vector<Email> coll{ "tom@domain.de", "jill@company.com",
                           "sarah@domain.de", "hana@company.com" };

  // remove all email addresses ending with ".de":
  auto newEnd = std::remove_if(coll.begin(), coll.end(),
                               [] (const Email& e) {
                                 auto&& val = e.getValue();
                                 return val.size() > 2 &&
                                        val.substr(val.size()-3) == ".de";
                               });

  // print elements up to the new end:
  std::cout << "remaining elements:\n";
  for (auto pos = coll.begin(); pos != newEnd; ++pos) {
     std::cout << "  '" << *pos << "'\n"; 
  }

  // print all elements in the container:
  std::cout << "all elements:\n";
  for (const auto& elem : coll) {
    std::cout << "  '" << elem << "'\n";
  }
}

