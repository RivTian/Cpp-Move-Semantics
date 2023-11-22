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


#include "geoobj.hpp"
#include "polygon.hpp"

int main()
{
  Polygon p0{"Poly1", {Coord{1,1}, Coord{1,9}, Coord{9,9}, Coord{9,1}}};
  Polygon p1{p0};             // copy
  Polygon p2{std::move(p0)};  // move

  p0.draw();
  p1.draw();
  p2.draw();
}

