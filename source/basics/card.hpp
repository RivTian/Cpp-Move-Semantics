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
#include <string>
#include <iostream>
#include <cassert>

void assertValidCard(const std::string& val)
{
    assert(val.find("seven") != std::string::npos ||
        val.find("eight") != std::string::npos ||
        val.find("nine") != std::string::npos ||
        val.find("ten") != std::string::npos ||
        val.find("jack") != std::string::npos ||
        val.find("queen") != std::string::npos ||
        val.find("king") != std::string::npos ||
        val.find("ace") != std::string::npos);
    assert(val.find("clubs") != std::string::npos ||
        val.find("spades") != std::string::npos ||
        val.find("hearts") != std::string::npos ||
        val.find("diamonds") != std::string::npos);
}

class Card
{
private:
    std::string value; // rank + "-of-" + suit
public:
    Card(const std::string& v)
        : value{v}
    {
        assertValidCard(value); // ensure the value is always valid
    }

    //...

    std::string getValue() const
    {
        return value;
    }

    friend std::ostream& operator<<(std::ostream& strm, const Card& c)
    {
        return strm << c.value;
    }
};
