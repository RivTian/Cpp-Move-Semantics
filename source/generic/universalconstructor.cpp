#include <iostream>
#include <fmt/core.h> // use fmt 3rd_party
#include <utility>

class X
{
public:
    X() = default;

    X (const X &x)
    {
        fmt::print("Copy Constructor\n");
    }

    X(X &&)
    {
        fmt::print("Move Constructor\n");
    }

    template<typename T>
    X(T &&)
    {
        fmt::print("universal Constructor\n");
    }
};

int main()
{
    X xv;
    const X xc;

    X xcc{xc};
    X xvc{xv};
    X Xvm{std::move(xv)};
    X xcm{std::move(xc)};
}
