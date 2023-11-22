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


#include "tasksbug.hpp"
#include <iostream>
#include <chrono>
#include <exception>

int main()
{
  try {
    Tasks ts;
    ts.start([]{
               std::this_thread::sleep_for(std::chrono::seconds{2});
               std::cout << "\nt1 done" << std::endl;
             });
    ts.start([]{
               std::cout << "\nt2 done" << std::endl;
             });

    // OOPS: move tasks:
    // Result in a fatal error
    Tasks other{std::move(ts)};
  }
  catch (const std::exception& e) {
    std::cerr << "EXCEPTION: " << e.what() << std::endl;
  }
}

