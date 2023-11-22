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
#include <thread>
#include <vector>

void doThis(const std::string& arg) {
  std::cout << "doThis(): " << arg << '\n';
}
void doThat(const std::string& arg) {
  std::cout << "doThat(): " << arg << '\n';
}

int main()
{
  std::vector<std::thread> threads;   // better std::jthread since C++20

  // start a couple of threads:
  std::string someArg{"Black Lives Matter"};
  threads.push_back(std::thread{doThis, someArg});
  threads.push_back(std::thread{doThat, std::move(someArg)});
  //...

  // wait for all threads to end:
  for (auto& t : threads) {
    t.join();
  }
}

