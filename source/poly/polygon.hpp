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


#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "geoobj.hpp"
#include <vector>
#include <iostream>

class Polygon : public GeoObj {
 private:
  std::vector<Coord> points;
 public:
  // constructor for name and list of Coords
  Polygon (std::string n, std::initializer_list<Coord> pl = {})
   : GeoObj{std::move(n)}, points{std::move(pl)} {
  }

  virtual void draw() const override {
    std::cout << "polygon '" << name << "' over";
    for (auto& p : points) {
      std::cout << " " << p;
    }
    std::cout << "\n";
  }
};

#endif

