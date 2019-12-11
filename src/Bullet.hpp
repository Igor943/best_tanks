
#ifndef _BULLET_HPP_
#define _BULLET_HPP_

#include "Engine.hpp"

struct Point;

class Bullet
{
public:
    Bullet(int x, int y, int direction);
    ~Bullet(void);
    Point const *get_cur_pos(void);
    void set_cur_pos(int x, int y);
    int get_direction(void);
private:
    Point *_pos;
    int _direction;
};

#endif /* _BULLET_HPP_ */