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


#include "initclassic.hpp"
#include "initmeasure.hpp"
#include <iostream>
#include <cstdlib>   // for std::atoi()

int main(int argc, const char** argv)
{
  int num = 1000;  // num iterations to measure
  if (argc > 1) {
    num = std::atoi(argv[1]);
  }

  // a few iterations to avoid measuring initial behavior:
  measure(5);

  // measure (in integral nano- and floating-point milliseconds):
  std::chrono::nanoseconds nsDur{measure(num)};
  std::chrono::duration<double, std::milli> msDur{nsDur};

  // print result:
  std::cout << num << " iterations take:  "
            << msDur.count() << "ms\n";
  std::cout << "3 inits take on average:  "
            << nsDur.count() / num << "ns\n";
}

