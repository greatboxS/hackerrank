#include <iostream>
using namespace std;
enum class Fruit
{
    apple,
    orange,
    pear
};
enum class Color
{
    red,
    green,
    orange
};

template <typename T>
struct Traits;

const char *fruit[3] = {"apple", "orange", "pear"};
const char *color[3] = {"red", "green", "orange"};

template <typename T>
struct Traits
{
    static const char *name(int index)
    {
        if (typeid(T) == typeid(Fruit))
        {
            if (index <= (int)Fruit::pear && index >= 0)
                return fruit[index];
        }
        if (typeid(T) == typeid(Color))
        {
            if (index <= (int)Color::orange && index >= 0)
                return color[index];
        }
        return "unknown";
    }
};

int main()
{
    int t = 0;
    std::cin >> t;

    for (int i = 0; i != t; ++i)
    {
        int index1;
        std::cin >> index1;
        int index2;
        std::cin >> index2;
        cout << Traits<Color>::name(index1) << " ";
        cout << Traits<Fruit>::name(index2) << "\n";
    }
}
