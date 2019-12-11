
#ifndef _FIELD_HPP_
#define _FIELD_HPP_

// #define MOVE_LEFT 100
// #define MOVE_RIGHT 101
// #define MOVE_UP 102
// #define MOVE_DOWN 103

#include "Engine.hpp"

class Unit;
class Bullet;

class Field
{
public:
    Field(void);
    void do_action(Unit &unit);
    void do_refresh(void);
    int get_rand_move(void);
    void move_unit(Unit &unit, int direction);
    ~Field(void);
private:
    char** _arena;
    int _arena_width;
    int _arena_height;
    std::vector<Bullet *> _vec_bullets;
};

#endif /* _FIELD_HPP_ */