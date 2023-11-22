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
#include <memory>

std::unique_ptr<std::string> source()
{
   static long id{0};
   
   // create string with new and let ptr own it:
   auto ptr = std::make_unique<std::string>("obj" + std::to_string(++id));   
   //...                                                 
   return ptr;        // transfer ownership to caller
}

int main()
{
   std::unique_ptr<std::string> p;
   for (int i = 0; i < 10; ++i) {
      p = source();   // p gets ownership of the returned object
                      // (previously returned object of source() is deleted)
      std::cout << *p << '\n';
      //...
   }
} // last-owned object of p is deleted

