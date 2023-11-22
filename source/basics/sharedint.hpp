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


#include <memory>
#include <string>

class SharedInt {
  private:
    std::shared_ptr<int> sp;
    // special ``value'' for moved-from objects:
    inline static std::shared_ptr<int> movedFromValue{std::make_shared<int>(0)};

  public:
    explicit SharedInt(int val) 
     : sp{std::make_shared<int>(val)} {
    }

    std::string asString() const {
      return std::to_string(*sp);   // OOPS: unconditional deref
    }

    // fix moving special member functions:
    SharedInt (SharedInt&& si) 
     : sp{std::move(si.sp)} {
        si.sp = movedFromValue;
    }
    SharedInt& operator= (SharedInt&& si) noexcept {
      if (this != &si) {
        sp = std::move(si.sp);
        si.sp = movedFromValue;
      }
      return *this;
    }

    // enable copying (deleted with user-declared move operations):
    SharedInt (const SharedInt&) = default;
    SharedInt& operator= (const SharedInt&) = default;
};

