#include <iostream>
#include <vector>

class Hotel
{
private:
    int bedrooms{};
    int bathrooms{};

public:
    Hotel(int bed, int bath) : bedrooms{bed}, bathrooms{bath}
    {
    }

    virtual int get_price()
    {
        return 50 * bedrooms + 100 * bathrooms;
    }
};

class Apartment : public Hotel
{
public:
    Apartment(int bed, int bath) : Hotel{bed, bath}
    {
    }

    int get_price() override
    {
        return Hotel::get_price() + 100;
    }
};

int main()
{
    int number{2};
    std::cin >> number;

    std::vector<Hotel *> rooms;

    for (int i = 0; i < number; i++)
    {
        std::string room_type{"apartment"};

        int bedroom{1};
        int bathroom{1};

        std::cin >> room_type >> bedroom >> bathroom;

        if (room_type == "standard")
        {
            rooms.push_back(new Hotel{bedroom, bathroom});
        }
        else
        {
            rooms.push_back(new Apartment{bedroom, bathroom});
        }
    }

    int total_profit{};

    for (auto room : rooms)
    {
        total_profit += room->get_price();
    }

    for (auto room : rooms)
    {
        delete room;
    }

    std::cout << total_profit << std::endl;
    return 0;
}