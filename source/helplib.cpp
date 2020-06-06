#include "helplib.hpp"

std::string int_to_str(int number)
{
    std::string str;
    std::string backwards;
    if (number < 0)
    {
        str = "-";
    }
    int div = number/10;
    while (div > 0)
    {
        backwards = backwards + static_cast<char>(number%10);
        number = div;
        div = number/10;
    }
    if (div == 0)
    {
        backwards = backwards + static_cast<char>(number%10);
    }
    for(ssize_t i = backwards.size() - 1; i >= 0; --i)
    {
        str = str + backwards[i];
    }
    return str;
}
