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

#pragma once
#include <array>
#include <thread>

class Tasks
{
public:
    Tasks() = default;

    // pass a new thread:
    template <typename T>
    void start(T op)
    {
        threads[numThreads] = std::thread{std::move(op)};
        ++numThreads;
    }

    //...

    // at the end wait for all started threads:
    ~Tasks()
    {
        for (int i = 0; i < numThreads; ++i)
        {
            threads[i].join();
        }
    }

private:
    std::array<std::thread, 10> threads; // array of threads for up to 10 tasks
    int numThreads{0}; // current number of threads/tasks
};
