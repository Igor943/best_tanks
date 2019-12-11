
#include "Bullet.hpp"

Bullet::Bullet(int x, int y, int direction)
{
    _pos = new Point;
    _pos->x = x;
    _pos->y = y; 
    _direction = direction;
}

Bullet::~Bullet(void)
{
    delete _pos;
}

Point const *Bullet::get_cur_pos(void)
{
    return (_pos);
}

void Bullet::set_cur_pos(int x, int y)
{
    _pos->x = x;
    _pos->y = y;
}

int Bullet::get_direction(void)
{
    return (_direction);
}