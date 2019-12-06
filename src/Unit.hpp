
#ifndef _Unit_HPP_
#define _Unit_HPP_

#include "Engine.hpp"

struct Point;

class Unit
{
public:
    Unit(int fd, int type, int x_pos, int y_pos);
    int get_fd(void);
    int get_type(void);
    int get_tank_width(void);
    int get_tank_height(void);
    Point const *get_cur_pos(void);
    void set_cur_point(int x, int y);
    ~Unit(void);

private:
    int _fd;
    int _type;
    int _tank_width;
    int _tank_height;
    Point *_pos;
};

#endif /* _Unit_HPP_ */