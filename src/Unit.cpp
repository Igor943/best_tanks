
#include "Unit.hpp"

Unit::Unit(int fd, int type, int x_pos, int y_pos)
{
    _fd = fd;
    _type = type;
    _pos = new Point;
    _pos->x = x_pos;
    _pos->y = y_pos;
    _tank_width = 6;
    _tank_height = 3;
}

int Unit::get_fd(void)
{
    return (_fd);
}

int Unit::get_type(void)
{
    return (_type);
}

int Unit::get_tank_width(void)
{
    return (_tank_width);
}

int Unit::get_tank_height(void)
{
    return (_tank_height);
}

Point const *Unit::get_cur_pos(void)
{
    return (_pos);
}

void Unit::set_cur_point(int x, int y)
{
    _pos->x = x;
    _pos->y = y;
}

Unit::~Unit(void)
{
    delete _pos;
}