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
#include <chrono>

// string wrapper with move constructor:
struct Str
{
    std::string val;

    // ensure each string has 100 characters:
    Str() : val(100, 'a')
    {
        // don't use braces here
    }

    // enable copying:
    Str(const Str&) = default;

    // enable moving (with and without noexcept):
    // 如果不添加 noexpect 则会有两倍的性能差距
    Str(Str&& s) noexcept
        : val{std::move(s.val)}
    {
    }
};

int main()
{
    // create vector of 1 Million wrapped strings:
    std::vector<Str> coll;
    coll.resize(1000000);

    // measure time to reallocate memory for all elements:
    auto t0 = std::chrono::steady_clock::now();
    coll.reserve(coll.capacity() + 1);
    auto t1 = std::chrono::steady_clock::now();

    std::chrono::duration<double, std::milli> d{t1 - t0};
    std::cout << d.count() << "ms\n";
}
