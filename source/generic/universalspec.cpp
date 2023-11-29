#include <string>
#include <fmt/core.h>
#include <utility>
#include <vector>

template<typename Coll, typename T>
void insert(Coll &coll, T&& arg)
{
  fmt::print("primary template for universal reference of type T\n");
  coll.push_back(arg);
}

// full specialization for const lvalues of type std::string:
template<>
void insert(std::vector<std::string>& coll, const std::string& arg)
{
  fmt::print("full specialization for type const std::string&\n");
  coll.push_back(arg);
}

// full specialization for non-const lvalues of type std::string:
template<>
void insert(std::vector<std::string>& coll, std::string& arg)
{
  fmt::print("full specialization for type std::string&\n");
  coll.push_back(arg);
}

// full specialization for non-const rvalues of type std::string:
template<>
void insert(std::vector<std::string>& coll, std::string&& arg)
{
  fmt::print("full specialization for type std::string&&\n");
  coll.push_back(arg);
}

// full specialization for const rvalues of type std::string:
template<>
void insert(std::vector<std::string>& coll, const std::string&& arg)
{
  fmt::print("full specialization for type const std::string&&\n");
  coll.push_back(arg);
}

int main()
{
  std::vector<std::string> coll;
  //...
  insert(coll, std::string{"prvalue"});  // calls full specialization for rvalues
  std::string str{"lvalue"};
  insert(coll, str);                     // calls full specialization for lvalues
  insert(coll, std::move(str));          // calls full specialization for rvalues

  const std::string cstr{"const lvalue"};
  insert(coll, cstr);                    // calls full specialization for const lvalues
  insert(coll, std::move(cstr));         // calls full specialization for const rvalues
}

