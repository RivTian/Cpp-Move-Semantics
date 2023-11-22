#include <iostream>
#include <fmt/core.h>
#include <utility>

using namespace fmt;

class C
{
public:
    void foo() const &
    {
        print("foo() const &\n");
    }

    void foo() &&
    {
        print("foo() &&\n");
    }

    void foo() &
    {
        print("foo() &\n");
    }

    void foo() const &&
    {
        print("foo() const &&\n");
    }
};

int main()
{
    C x;
    x.foo();
    C{}.foo();
    std::move(x).foo();

    const C cx;
    cx.foo();
    std::move(cx).foo();
}
