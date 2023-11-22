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

int main()
{
  std::string s0;
  std::string s1{"short"};
  std::string s2{"a string with an extraordinarily long value"};
  std::cout << "- s0 capa: " << s0.capacity() << " ('" << s0 << "')\n";
  std::cout << "  s1 capa: " << s1.capacity() << " ('" << s1 << "')\n";
  std::cout << "  s2 capa: " << s2.capacity() << " ('" << s2 << "')\n";

  std::string s3{std::move(s1)};
  std::string s4{std::move(s2)};
  std::cout << "- s1 capa: " << s1.capacity() << " ('" << s1 << "')\n";
  std::cout << "  s2 capa: " << s2.capacity() << " ('" << s2 << "')\n";
  std::cout << "  s3 capa: " << s3.capacity() << " ('" << s3 << "')\n";
  std::cout << "  s4 capa: " << s4.capacity() << " ('" << s4 << "')\n";

  std::string s5{"quite a reasonable value"};
  std::cout << "- s4 capa: " << s4.capacity() << " ('" << s4 << "')\n";
  std::cout << "  s5 capa: " << s5.capacity() << " ('" << s5 << "')\n";

  s4 = std::move(s5);
  std::cout << "- s4 capa: " << s4.capacity() << " ('" << s4 << "')\n";
  std::cout << "  s5 capa: " << s5.capacity() << " ('" << s5 << "')\n";
}

