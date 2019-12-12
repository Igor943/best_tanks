
#include "Unit.hpp"

Unit::Unit(int type, int x_pos, int y_pos)
{
    _type = type;
    _pos = new Point;
    _pos->x = x_pos;
    _pos->y = y_pos;
    _tank_width = 6;
    _tank_height = 3;
    struct itimerspec new_value;
    new_value.it_interval.tv_sec = 0;
    if (type == LOC_USER_TANK || type == SOC_USER_TANK)
    {
        new_value.it_interval.tv_nsec = 150000000;
    }
    else if (type == AI_TANK)
    {
        new_value.it_interval.tv_nsec = 250000000;
    }
    new_value.it_value.tv_sec = 1;
    new_value.it_value.tv_nsec = 1;
    int timer = timerfd_create(CLOCK_MONOTONIC, 0);
    timerfd_settime(timer, 0, &new_value, NULL);
    _fd = timer;
    if (type == SOC_USER_TANK)
    {
        int listener;
        struct sockaddr_in addr;
        listener = socket(AF_INET, SOCK_STREAM, 0);
        addr.sin_family = AF_INET;
        addr.sin_port = htons(3427);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        bind(listener, (struct sockaddr *)&addr, sizeof(addr));
        listen(listener, 10);
        _fd = listener;
    }
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