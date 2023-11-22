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


#include "customerimpl.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<Customer> coll;
    // coll.reserve(12); // 为什么不写 reserve 的时候会出现 copy 则是因为其大小在变化，需要重新分配内存
    for (int i = 0; i < 12; ++i)
    {
        // coll.push_back("TestCustomer" + std::to_string(i - 5));
        coll.push_back(Customer{"TestCustomer " + std::to_string(i - 5)});
    }

    std::cout << "----sort():\n";
    std::sort(coll.begin(), coll.end(),
              [](const Customer& c1, const Customer& c2)
              {
                  return c1.getName() < c2.getName();
              });
}
