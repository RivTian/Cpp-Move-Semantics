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
  Person(const std::string& f, std::string&& l)
   : first{f}, last{std::move(l)} {
  }
  Person(std::string&& f, const std::string& l)
   : first{std::move(f)}, last{l} {
  }
  Person(std::string&& f, std::string&& l)
   : first{std::move(f)}, last{std::move(l)} {
  }
  Person(const char* f, const char* l)
   : first{f}, last{l} {
  }
  Person(const char* f, const std::string& l)
   : first{f}, last{l} {
  }
  Person(const char* f, std::string&& l)
   : first{f}, last{std::move(l)} {
  }
  Person(const std::string& f, const char* l)
   : first{f}, last{l} {
  }
  Person(std::string&& f, const char* l)
   : first{std::move(f)}, last{l} {
  }
  //...
};

