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

void process(const std::string&) {
  std::cout << "process(const std::string&)\n";
}
void process(std::string&) {
  std::cout << "process(std::string&)\n";
}
void process(std::string&&) {
  std::cout << "process(std::string&&)\n";
}

const std::string& computeConstLRef(const std::string& str) {
  return str;
}
std::string& computeLRef(std::string& str) {
  return str;
}
std::string&& computeRRef(std::string&& str) {
  return std::move(str);
}
std::string computeValue(const std::string& str) {
  return str;
}

int main()
{
  auto&& r1 = computeConstLRef("tmp");
  process(std::forward<decltype(r1)>(r1));     // calls process(const std::string&)

  std::string str{"lvalue"};
  auto&& r2 = computeLRef(str);
  process(std::forward<decltype(r2)>(r2));     // calls process(std::string&)

  auto&& r3 = computeRRef("tmp");
  process(std::forward<decltype(r3)>(r3));     // calls process(std::string&&)
  auto&& r4 = computeRRef(std::move(str));
  process(std::forward<decltype(r4)>(r4));     // calls process(std::string&&)

  auto&& r5{computeValue("tmp")};
  process(std::forward<decltype(r5)>(r5));     // calls process(std::string&&)
}

