
#include "User.hpp"

User::User(int fd)
{
    _fd = fd;
    _tank_width = 3;
    _tank_height = 3;
}

int User::get_fd(void)
{
    return (_fd);
}

int User::get_tank_width(void)
{
    return (_tank_width);
}

int User::get_tank_height(void)
{
    return (_tank_height);
}

User::~User(void)
{
    return ;
}