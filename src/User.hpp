
#ifndef _USER_HPP_
#define _USER_HPP_

#include "Engine.hpp"

struct Point;

class User
{
public:
    User(int fd, int x_pos, int y_pos);
    int get_fd(void);
    int get_tank_width(void);
    int get_tank_height(void);
    Point const *get_cur_pos(void);
    void set_cur_point(int x, int y);
    ~User(void);

private:
    int _fd;
    int _tank_width;
    int _tank_height;
    int _lvl;
    Point *_pos;
};

#endif /* _USER_HPP_ */