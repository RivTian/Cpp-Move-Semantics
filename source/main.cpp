#include <iostream>
#include <fmt/core.h>
#include <utility>

void foo(const std::string &)
{
    fmt::print("foo(const string &)\n");
}

void foo(std::string &)
{
    fmt::print("foo(string &)\n");
}

void foo(std::string &&)
{
    fmt::print("foo(string &&)\n");
}

template<typename T>
void callFoo(T && arg)
{
    foo(std::forward<T>(arg));;
}

int main()
{
    std::string v = "hello";
    const std::string c = "world";

    // 完美转发相关
    callFoo(v);
    callFoo(c);
    callFoo(std::string{"demo.."});
    callFoo(std::move(v));
    std::string demo = std::move(v); // 转发
    callFoo(std::move(c));
}
