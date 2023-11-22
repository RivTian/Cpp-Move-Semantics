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

// primary template taking a universal reference:
template<typename Coll, typename T>
void insert(Coll& coll, T&& arg) 
{
  std::cout << "primary template for universal reference of type T\n";
  coll.push_back(arg);
}

// full specialization for const lvalues of type std::string:
template<>
void insert(std::vector<std::string>& coll, const std::string& arg) 
{
  std::cout << "full specialization for type const std::string&\n";
  coll.push_back(arg);
}

// full specialization for non-const lvalues of type std::string:
template<>
void insert(std::vector<std::string>& coll, std::string& arg) 
{
  std::cout << "full specialization for type std::string&\n";
  coll.push_back(arg);
}

// full specialization for non-const rvalues of type std::string:
template<>
void insert(std::vector<std::string>& coll, std::string&& arg) 
{
  std::cout << "full specialization for type std::string&&\n";
  coll.push_back(arg);
}

// full specialization for const rvalues of type std::string:
template<>
void insert(std::vector<std::string>& coll, const std::string&& arg) 
{
  std::cout << "full specialization for type const std::string&&\n";
  coll.push_back(arg);
}

int main()
{
  std::vector<std::string> coll;
  //... 
  insert(coll, std::string{"prvalue"});  // calls full specialization for rvalues
  std::string str{"lvalue"};
  insert(coll, str);                     // calls full specialization for lvalues
  insert(coll, std::move(str));          // calls full specialization for rvalues

  const std::string cstr{"const lvalue"};
  insert(coll, cstr);                    // calls full specialization for const lvalues
  insert(coll, std::move(cstr));         // calls full specialization for const rvalues
}

