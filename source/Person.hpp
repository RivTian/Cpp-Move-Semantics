#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <utility>

class Person
{
public:
    std::string getName() &&
    {
        return std::move(name);
    }

    const std::string & getName() const &
    {
        return name;
    }

    explicit Person(const std::string& name)
        : name(name)
    {
    }

private:
    std::string name;
};

#endif //PERSON_HPP
