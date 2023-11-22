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


#include "card.hpp"
#include <iostream>
#include <string>
#include <vector>

void print(const Card& c)
{
    std::string val{c.getValue()};
    auto pos = val.find("-of-");
    auto p2 = pos + 4;
    std::cout << val.substr(0, pos) << ' '
        << val.substr(pos + 4) << '\n';
}

int main() // Bug Exist, Look P98
{
    std::vector<Card> deck;

    for (auto suit : {"clubs", "spades", "hearts", "diamonds"})
    {
        for (auto rank : {
                 "seven", "eight", "nine", "ten",
                 "jack", "queen", "king", "ace"
             })
        {
            deck.push_back(rank + std::string{"-of-"} + suit);
        }
    }

    for (const auto& c : deck)
    {
        std::cout << c << '\n';
    }
    print(deck[0]); // passing a valid object

    Card c{std::move(deck[0])}; // deck[0] has invalid state
    print(deck[0]); // passing an object with broken invariant
    deck[0] = Card{"ace-of-hearts"}; // deck[0] is valid again
    print(deck[0]); // passing a valid object
}
