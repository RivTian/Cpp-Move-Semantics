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
#include <thread>
#include <future>

void getValue(std::promise<std::string> p)
{
    try
    {
        std::string ret{"vote"};
        //...
        // store result:
        p.set_value_at_thread_exit(std::move(ret));
    }
    catch (...)
    {
        // store exception:
        p.set_exception_at_thread_exit(std::current_exception());
    }
}

int main()
{
    std::vector<std::future<std::string>> results;

    // create promise and future to deal with outcome of the thread started:
    std::promise<std::string> p;
    std::future<std::string> f{p.get_future()};
    results.push_back(std::move(f));

    // start thread and move the promise to it:
    std::thread t{getValue, move(p)};
    t.detach(); // would not be necessary for std::jthread
    //...

    // wait for all threads to end:
    for (auto& fut : results)
    {
        std::cout << fut.get() << '\n';
    }
}
