
#include "User.hpp"

User::User(int fd, int x_pos, int y_pos)
{
    _fd = fd;
    _pos = new Point;
    _pos->x = x_pos;
    _pos->y = y_pos;
    _tank_width = 6;
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

Point const *User::get_cur_pos(void)
{
    return (_pos);
}

void User::set_cur_point(int x, int y)
{
    _pos->x = x;
    _pos->y = y;
}

User::~User(void)
{
    delete _pos;
}