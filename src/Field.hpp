
#ifndef _FIELD_HPP_
#define _FIELD_HPP_

#include "Engine.hpp"

class Unit;

class Field
{
public:
    Field(void);
    void do_action(Unit *unit);
    void do_refresh(void);
    int get_rand_move(void);
    void move_unit(Unit *unit, int direction);
    ~Field(void);
private:
    char** _arena;
    int _arena_width;
    int _arena_height;
};

#endif /* _FIELD_HPP_ */