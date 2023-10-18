#include <iostream>

class Person
{
private:
    std::string first_name {};
    std::string last_name {};

public:
    Person(std::string first, std::string last) : first_name{first}, last_name{last} 
    {

    }

    std::string& get_first_name()
    {
        return first_name;
    } 

    std::string& get_last_name()
    {
        return last_name;
    }

    friend std::ostream& operator<< (std::ostream& out, const Person& p);
};

std::ostream& operator<< (std::ostream& out, const Person& p) 
{
    out << "first_name="+p.first_name << ",last_name="+p.last_name;

    return out;
}

int main() {
    std::string first_name {};
    std::string last_name {};
    std::string additional {};

    std::cin >> first_name >> last_name >> additional;

    Person p{first_name, last_name};

    std::cout << p << " " << additional << std::endl;

    return 0;
}