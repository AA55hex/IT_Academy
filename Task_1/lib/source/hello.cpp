#include <iostream>
#include <experimental/string_view>

std::ostream& send(std::ostream& ost, std::experimental::string_view str)
{
    ost << "Message from library: " << str << std::endl;
    return ost;
}
