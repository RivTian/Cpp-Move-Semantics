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
#include <utility>

template<typename Coll, typename T>
void insertBoth(Coll& coll, T&& p)
{
  // if p has move semantics, move a value but copy reference/static members
  coll.push_back(std::forward<T>(p).first);  
  coll.push_back(std::forward<T>(p).second); 
}

int main()
{
  std::string s{"outside"};
  std::pair<std::string, std::string> p1{"p1first", "p1second"};
  std::pair<std::string, std::string&> p2{"p2first", s};  // note: reference member

  std::vector<std::string> coll;

  insertBoth(coll, p1);              // does copy both members
  std::cout << "p1.first:  " << p1.first << '\n';
  std::cout << "p1.second: " << p1.second << '\n';

  insertBoth(coll, std::move(p1));   // does move both value members
  std::cout << "p1.first:  " << p1.first << '\n';
  std::cout << "p1.second: " << p1.second << '\n';

  insertBoth(coll, std::move(p2));   // does move value and copy reference member
  std::cout << "p2.first:  " << p2.first << '\n';
  std::cout << "p2.second: " << p2.second << '\n';
   
  std::cout << "coll:\n";
  for (const auto& elem : coll) {
     std::cout << "- elem: " << elem << '\n';
  }
}

